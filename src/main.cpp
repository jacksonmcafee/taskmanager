#include "Controller.h"
#include "usage_messages.h"
#include "commands.h"
#include <iomanip>

void parseInput(const std::string& input, std::vector<std::string>& result);
std::string condenseArgv(char** charArray);
bool handleCommand(Controller& controller, std::vector<std::string>& parsed);
CommandType getCommand(std::string commandStr);
const char* GetCommandUsage(CommandType command);
std::chrono::system_clock::time_point parseDate(std::string date);

int main(int argc, char* argv[]) {
  // instantiate controller
  Controller controller;
 
  // initialze loop control 
  bool continueLoop = true;

  // initialize necessary strings and vector 
  std::string input;
  std::vector<std::string> parsed;

  // handle single-command input  
  if (argc > 1) {
    // parse input 
    input = condenseArgv(argv);
    parsed.clear();
    parseInput(input, parsed);

    // handle command and return
    handleCommand(controller, parsed);
    return 0;
  }
    
  // handle interactive input
  std::cout << "Entering interactive mode. Type 'help' for a list of commands.\n\n";
  while (continueLoop && std::getline(std::cin, input)) {
    // parse input
    parsed.clear();
    parseInput(input, parsed);

    // handle command and set continueLoop
    continueLoop = handleCommand(controller, parsed);
  }
  return 0;
} 

void parseInput(const std::string& input, std::vector<std::string>& result) {
    // use a stringstream to tokenize the input
    std::istringstream iss(input);

    // parse & add quoted strings to the vector
    std::string token;
    while (iss >> std::quoted(token)) {
        result.push_back(token);
    }
}

// converts char** into a space-delimited string
std::string condenseArgv(char** charArray) {
    std::ostringstream oss;

    // start at element 1 to ignore calling command
    for (int i = 1; charArray[i] != nullptr; ++i) {
        if (i > 1) {
            oss << " "; // Add space before the second and subsequent elements
        }
        // keep quotation marks in-place for parsing
        oss << '"' << charArray[i] << '"';
    }

    return oss.str();
}

// handle a passed command after parsing
bool handleCommand(Controller& controller, std::vector<std::string>& parsed) {
  // get command if it exists
  // otherwise, command is CommandType::NONE
  CommandType command;
  if (parsed.size() > 0) {
    // parsed has some number of args, try to handle command
    command = getCommand(parsed.at(0));
  } else {
    // parsed is empty, do not handle
    return true;
  }

  // initialize variables before switch
  std::string str1, str2;
  int index;
  std::chrono::system_clock::time_point date;

  // handle commands
  switch (command) {
    case CommandType::ADD:
      // get str1 / str2 args, print usage if needed
      if (parsed.size() > 1) {
          str1 = parsed.at(1);
          str2 = (parsed.size() > 2) ? parsed.at(2) : "";

          // TODO: now() should be standardized to something like epoch
          date = (parsed.size() > 3) ? parseDate(parsed.at(3)) : std::chrono::system_clock::now();

          if (controller.AddTask(str1, str2, date)) {
              std::cout << "Successfully added a new task.\n";
          } else {
              std::cout << "Failed to add a new task.\n";
          }
      } else {
          std::cerr << "No name passed, task cannot be created.\n";
          std::cerr << GetCommandUsage(command) << "\n";
      }
      break;
   case CommandType::DELETE: 
      // delete task
      if (parsed.size() > 1 && isdigit(parsed.at(1)[0])) {
          // check if index is a valid integer
          index = stoi(parsed.at(1));

          // check if DeleteTask was successful
          if (controller.DeleteTask(index)) {
              std::cout << "Successfully deleted a task.\n";
          }
      } else {
          // stoi failed to parse argument or insufficient arguments
          // print proper usage message
          std::cerr << "Invalid or missing index for the 'delete' command.\n";
          std::cerr << GetCommandUsage(command) << "\n";
      }
      break;
    case CommandType::EDIT:
      // get index & name/desc flag
      if (parsed.size() >= 4) {
          // check if index is a valid integer
          if (isdigit(parsed.at(1)[0])) {
              index = stoi(parsed.at(1));
              
              // check if the second argument is "name" or "description"
              if (parsed.at(2) == "name" || parsed.at(2) == "description") {
                  // call EditTask if everything is valid
                  controller.EditTask(index, parsed.at(2), parsed.at(3));
              } else {
                  std::cerr << "Middle argument must be 'name' or 'description'\n";
                  std::cerr << GetCommandUsage(command) << "\n";
              }
          } else {
              // stoi failed to parse argument, print proper usage message
              std::cerr << "Passed value '" << parsed.at(1) << "' is invalid.\n";
              std::cerr << GetCommandUsage(command) << "\n";
          }
      } else {
          // not enough arguments, print proper usage message
          std::cerr << "Insufficient arguments for the 'edit' command.\n";
          std::cerr << GetCommandUsage(command) << "\n";
      }
      break;
    case CommandType::LIST:
      if (!controller.ShowTasks()) {
        std::cout << "Your tasklist is empty.\n";
      }
      break;
    case CommandType::SHOW:
      // get index
      if (parsed.size() >= 2 && isdigit(parsed.at(1)[0])) {
          // check if index is a valid integer
          index = stoi(parsed.at(1));

          // call ShowTask if everything is valid
          controller.ShowTask(index);
      } else {
          // stoi failed to parse argument or insufficient arguments
          // print proper usage message
          std::cerr << "Invalid or missing index for the 'show' command.\n";
          std::cerr << GetCommandUsage(command) << "\n";
      }
      break;
    case CommandType::QUIT:
      return false;
    case CommandType::HELP:
      // check if extra arg was passed 
      if (parsed.size() > 1) {
        // get command and print usage information
        command = getCommand(parsed.at(1));
        std::cout << GetCommandUsage(command) << "\n";
      } else {
        // print general usage 
        std::cout << UsageMessages::GetHelpUsage() << "\n";
        std::cout << "Commands: " + commandList + "\n";
      }
      break;
    default:
      if (parsed.size() > 0) {
        std::cout << "Command '" << parsed.at(0) << "' not recognized.\n";
      }
  }
  std::cout << "\n";
  return true;
}

// returns a mapped command when passed a string
CommandType getCommand(std::string commandStr) {
  auto it = commandMap.find(commandStr); 
  if (it != commandMap.end()) {
    return it->second;
  }
  return CommandType::NONE;
}

// returns usage text for a given command
const char* GetCommandUsage(CommandType command) {
  switch (command) {
    case CommandType::ADD:
      return UsageMessages::GetAddUsage();
      break;
    case CommandType::DELETE:
      return UsageMessages::GetDeleteUsage();
      break;
    case CommandType::EDIT:
      return UsageMessages::GetEditUsage();
      break;
    case CommandType::SHOW:
      return UsageMessages::GetShowUsage();
      break;
     case CommandType::QUIT:
      return UsageMessages::GetQuitUsage();
      break;   
    default:
      return UsageMessages::GetHelpUsage();
  }
}

std::chrono::system_clock::time_point parseDate(std::string date) {
  // create a stringstream to parse the input string
  std::istringstream dateStream(date);

  // extract month, day, and year from the string
  int month, day, year;
  char delimiter;

  dateStream >> month >> delimiter >> day >> delimiter >> year;

  // check if parsing was successful
  if (dateStream.fail() || dateStream.bad()) {
    // TODO: now() should be standardized to something like epoch
    return std::chrono::system_clock::now();
  }

  // convert to tm structure
  std::tm timeInfo = {};
  timeInfo.tm_mon = month - 1;  // adjust month to be zero-based
  timeInfo.tm_mday = day;
  timeInfo.tm_year = year + 100;  // adjust year (assuming years in "YY" format)

  // convert to time_point
  std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(std::mktime(&timeInfo));

  return timePoint;
}

/*
  auto tVec = controller.SearchTasks("OtherName");
  for (auto tuple : tVec) {
    std::cout << std::get<0>(tuple) << ", " << std::get<1>(tuple).getName() << "\n";
  }
*/

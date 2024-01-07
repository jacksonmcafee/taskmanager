#include "Controller.h"
#include "usage_messages.h"
#include "commands.h"
#include <sstream>
#include <iomanip>

void parseInput(const std::string& input, std::vector<std::string>& result);
std::string condenseArgv(char** charArray);
bool handleCommand(Controller& controller, std::vector<std::string>& parsed);
CommandType getCommand(std::string commandStr);

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
            oss << " "; // Add space delimiter before the second and subsequent elements
        }
        // keep quotation marks in-place for parsing
        oss << '"' << charArray[i] << '"';
    }

    return oss.str();
}

// handle a passed command after parsing
bool handleCommand(Controller& controller, std::vector<std::string>& parsed) {
  // get command if it exists
  // otherwise, command is of type CommandType::NONE
  CommandType command;
  try {
    command = getCommand(parsed.at(0));
  } catch (const std::out_of_range& oor) {
    // parsed is empty, no arg passed, don't handle
    return true;
  }

  // initialize variables before switch
  std::string str1, str2;
  int index;

  // handle commands
  switch (command) {
    case CommandType::ADD:
      // handle out of range access
      try { str1 = parsed.at(1); }
      catch (const std::out_of_range& oor) { 
        str1 = "";
        std::cerr << "No name passed, task cannot be created.\n"; 
        std::cerr << UsageMessages::GetAddUsage() << "\n";
      }
      try { str2 = parsed.at(2); } 
      catch (const std::out_of_range& oor) { str2 = ""; }

      if (controller.AddTask(str1, str2)) {
        std::cout << "Successfully added a new task.\n";
      } else {
        // NOTE: Is this explicitly necessary?
        // Already warned about nameless creation above?
        std::cout << "Failed to add a new task.\n";
      } 
      break;
    case CommandType::DELETE:
      try {
        // convert index string to int and delete
        index = stoi(parsed.at(1));
        if (controller.DeleteTask(index)) {
          std::cout << "Successfully deleted a task.\n";
        }
      } catch (const std::invalid_argument& ia) {
        // stoi failed to parse argument, print proper usage message
        std::cerr << "Passed value '" << parsed.at(1) << "' is invalid.\n";
        std::cerr << UsageMessages::GetDeleteUsage() << "\n";
      } catch (const std::out_of_range& oor) {
        // index is outside of the range of parsed, print proper usage message
        std::cerr << "Passed index is out of range.\n";
        std::cerr << UsageMessages::GetDeleteUsage() << "\n"; 
      }
      break;
    case CommandType::EDIT:
      try {
        // get index & name/desc flag
        index = stoi(parsed.at(1));
        if (parsed.at(2) != "name" && parsed.at(2) != "description") {
          throw std::runtime_error("");
        }
        controller.EditTask(index, parsed.at(2), parsed.at(3));
      } catch (const std::invalid_argument& ia) {
        // stoi failed to parse argument, print proper usage message
        std::cerr << "Passed value '" << parsed.at(1) << "' is invalid.\n";
        std::cerr << UsageMessages::GetEditUsage() << "\n";
      } catch (const std::out_of_range& oor) {
        // index is outside of the range of parsed, print proper usage message
        std::cerr << "Passed index is out of range.\n";
        std::cerr << UsageMessages::GetEditUsage() << "\n"; 
      } catch (const std::runtime_error& re) {
        std::cerr << "Middle argument must be 'name' or 'description'\n";
        std::cerr << UsageMessages::GetEditUsage() << "\n";
      }
      break;
    case CommandType::LIST:
      if (!controller.ShowTasks()) {
        std::cout << "Your tasklist is empty.\n";
      }
      break;
    case CommandType::SHOW:
      try {
        index = stoi(parsed.at(1));
        controller.ShowTask(index);
      } catch (const std::invalid_argument& ia) {
        // stoi failed to parse argument, print proper usage message
        std::cerr << "Passed value '" << parsed.at(1) << "' is invalid.\n";
        std::cerr << UsageMessages::GetShowUsage() << "\n";
      } catch (const std::out_of_range& oor) {
        // index is outside of the range of parsed, print proper usage message
        std::cerr << "Passed index is out of range.\n";
        std::cerr << UsageMessages::GetShowUsage() << "\n";
      }
      break;
    case CommandType::QUIT:
      return false;
    case CommandType::HELP:
      std::cout << UsageMessages::GetHelpUsage() << "\n";
      std::cout << "Commands: " + commandList + "\n";
      break;
    default:
      try { 
        std::cout << "Command '" << parsed.at(0) << "' not recognized.\n";
      } catch (const std::out_of_range& oor) {
        ;
      }
  }
  std::cout << "\n";
  return true;
}

CommandType getCommand(std::string commandStr) {
  auto it = commandMap.find(commandStr); 
  if (it != commandMap.end()) {
    return it->second;
  }
  return CommandType::NONE;
}

/*
  auto tVec = controller.SearchTasks("OtherName");
  for (auto tuple : tVec) {
    std::cout << std::get<0>(tuple) << ", " << std::get<1>(tuple).getName() << "\n";
  }
*/

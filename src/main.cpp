#include "Controller.h"
#include "usage_messages.h"
#include "commands.h"
#include <sstream>
#include <iomanip>

void parseInput(const std::string& input, std::vector<std::string>& result);
std::string condenseArgv(char** charArray);
bool handleCommand(Controller& controller, std::vector<std::string>& parsed);

int main(int argc, char* argv[]) {
  // instantiate controller
  Controller controller;
 
  // initialze loop control 
  bool continueLoop = true;

  // initialize necessary strings and vector 
  std::string input;
  std::vector<std::string> parsed;

  // handle command input  
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
            oss << " "; // Add the delimiter before the second and subsequent elements
        }
        oss << charArray[i];
    }

    return oss.str();
}

// handle a passed command after parsing
bool handleCommand(Controller& controller, std::vector<std::string>& parsed) {
  // get command if it exists
  // otherwise, command is of type CommandType::NONE
  CommandType command;
  auto it = commandMap.find(parsed.at(0));
  if (it != commandMap.end()) {
    command = it->second;
  } else {
    command = CommandType::NONE
  }

  // initialize string variables
  std::string str1, str2;

  // handle commands
  switch (command) {
    case CommandType::ADD:
      // handle out of range access
      // TODO: Warn if no name or desc were passed, use GetAddUsage()
      str1 = (parsed.size() > 1) ? parsed.at(1) : "no name";
      str2 = (parsed.size() > 2) ? parsed.at(2) : "no description";
      controller.AddTask(str1, str2);
      break;
    case CommandType::DELETE:
      // validate deletion index
      try {
        // convert index string to int and delte
        controller.DeleteTask(stoi(parsed.at(1)));
      } catch (const std::invalid_argument& ia) {
        std::cerr << "Passed value '" << parsed.at(1) << "' is invalid.\n";
        std::cerr << UsageMessages::GetDeleteUsage() << "\n";
      } catch (const std::out_of_range& oor) {
        std::cerr << oor.what() << "\n";
        std::cerr << UsageMessages::GetDeleteUsage() << "\n"; 
      }
      break;
    case CommandType::LIST:
      controller.ShowTasks();
      break;
    case CommandType::SHOW:
      controller.ShowTask(parsed.at(1));
      break;
    case CommandType::QUIT:
      return false;
    default:  
      std::cout << "Command '" << parsed.at(0) << "' not recognized.\n";
  }
  return true;
}

/*
  auto tVec = controller.SearchTasks("OtherName");
  for (auto tuple : tVec) {
    std::cout << std::get<0>(tuple) << ", " << std::get<1>(tuple).getName() << "\n";
  }
*/

#include "Controller.h"
#include <sstream>
#include <iomanip>

void parseInput(const std::string& input, std::string& command, std::vector<std::string>& result);

int main(int argc, char* argv[]) {
  // instantiate controller
  Controller controller;
 
  // initialize input string and array 
  std::string input, command;
  std::vector<std::string> parsed;
    
  // enter input loop until user decides to exit
  while (std::getline(std::cin, input)) {
    parsed.clear();
    parseInput(input, command, parsed);
  
    // read first arg to determine command
    if (command == "add") {
      controller.AddTask(parsed[0], parsed[1]);
    } else if (command == "delete") {
      controller.DeleteTask(stoi(parsed[0]));
    } else if (command == "list") {
      controller.ShowTasks();
    } else if (command == "quit") {
      break;
    } else {
      std::cout << "Command '" << command << "' not recognized.\n";
    }
  }

  return 0;
}

void parseInput(const std::string& input, std::string& command, std::vector<std::string>& result) {
    // use a stringstream to tokenize the input
    std::istringstream iss(input);

    // parse out command
    iss >> command;

    // parse & add quoted strings to the vector
    std::string token;
    while (iss >> std::quoted(token)) {
        result.push_back(token);
    }
}

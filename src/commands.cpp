#include "commands.h"

std::map<std::string, CommandType> commandMap = {
    {"add", CommandType::ADD},
    {"delete", CommandType::DELETE},
    {"edit", CommandType::EDIT},
    {"list", CommandType::LIST},
    {"show", CommandType::SHOW},
    {"quit", CommandType::QUIT},
    {"help", CommandType::HELP},
};

std::string commandList = "add, delete, edit, list, show, quit, help";

// returns a mapped command when passed a string
CommandType getCommand(std::string commandStr) {
  auto it = commandMap.find(commandStr); 
  if (it != commandMap.end()) {
    return it->second;
  }
  return CommandType::NONE;
}



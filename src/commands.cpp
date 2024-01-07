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

#include "commands.h"

std::map<std::string, CommandType> commandMap = {
    {"add", CommandType::ADD},
    {"delete", CommandType::DELETE},
    {"list", CommandType::LIST},
    {"show", CommandType::SHOW},
    {"quit", CommandType::QUIT},
    {"help", CommandType::HELP},
};

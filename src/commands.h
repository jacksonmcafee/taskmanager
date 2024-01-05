#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>

enum class CommandType {
    NONE,
    ADD,
    DELETE,
    LIST,
    SHOW,
    QUIT,
    HELP,
};

extern std::map<std::string, CommandType> commandMap;

#endif // COMMANDS_H

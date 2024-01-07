#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>

enum class CommandType {
    NONE,
    ADD,
    DELETE,
    EDIT,
    LIST,
    SHOW,
    QUIT,
    HELP,
};

extern std::map<std::string, CommandType> commandMap;
extern std::string commandList;

#endif // COMMANDS_H

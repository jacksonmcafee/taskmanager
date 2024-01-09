#include "usage_messages.h"


namespace UsageMessages {
    const char* GetAddUsage() {
        return "Adds a new item with the specified name and description.\nUsage: add [name] [description]";
    }

    const char* GetDeleteUsage() {
        return "Deletes the item at the specified index.\nUsage: delete [index]";
    }

    const char* GetEditUsage() {
        return "Edits the specified property (name or description) of the task at the given index with the new value.\nUsage: edit [index] [name | description] [value]";
    }

    const char* GetShowUsage() {
        return "Shows details of the task at the specified index.\nUsage: show [index]";
    }

    const char* GetHelpUsage() {
        return "Displays help information for a specific command, or general help if no command is specified.\nUsage: help [command]";
    }

    const char* GetQuitUsage() {
        return "Exits the application.\nUsage: quit";
    }

    const char* GetListUsage() {
        return "Lists all current tasks.\nUsage: list";
    }
}

#include "usage_messages.h"

namespace UsageMessages {
    const char* GetAddUsage() {
      return "Usage: add [name] [description]";
    }

    const char* GetDeleteUsage() {
      return "Usage: delete [index]";
    }

    const char* GetEditUsage() {
      return "Usage: edit [index] [name | description] [value]";
    }

    const char* GetShowUsage() {
      return "Usage: show [index]";
    }

    const char* GetHelpUsage() {
      return "Usage: help [command]";
    }

    const char* GetQuitUsage() {
      return "Usage: quit";
    }
    
    const char* GetListUsage() {
      return "Usage: list";
    }
}

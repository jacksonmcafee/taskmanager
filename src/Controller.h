#pragma once

#include "Task.h"
#include <tuple>

class Controller {
  public:
    // constructor & destructor
    Controller();
    ~Controller();

    // tasklist modification 
    bool AddTask(std::string name, std::string description);
    bool DeleteTask(size_t index);
    bool EditTask(int index, std::string value, std::string nd);
    void ClearTaskList();
  
    // tasklist display
    void ShowTask(size_t index);
    void ShowTasks();
 
    // search for tasks
    std::vector<std::tuple<int, Task>> SearchTasks(std::string search);
    
    // tasklist
    std::vector<Task> taskList;
    std::string file;

  private:
    bool validateIndex(size_t index) {
      if (index < 0 || index >= taskList.size()) {
        return false;
      } else {
        return true;
      }
    }
};

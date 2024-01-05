#pragma once

#include "Task.h"
#include <tuple>

class Controller {
  public:
    // constructor & destructor
    Controller();
    ~Controller();

    // tasklist modification 
    void AddTask(std::string name, std::string description);
    void AddTask(Task task);
    bool DeleteTask(size_t index);
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

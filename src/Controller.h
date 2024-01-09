#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Task.h"
#include <tuple>

class Controller {
  public:
    // constructor & destructor
    Controller();
    ~Controller();

    // tasklist modification 
    bool AddTask(std::string name, std::string description, std::chrono::system_clock::time_point due_date);
    bool DeleteTask(size_t index);
    bool EditTask(int index, std::string value, std::string nd);
    void ClearTasklist();
  
    // tasklist display
    void ShowTask(size_t index);
    bool ShowTasks();
 
    // search for tasks
    std::vector<std::tuple<int, Task>> SearchTasks(std::string search);
    
    // tasklist
    std::vector<Task> tasklist;
    std::string file;

  private:
    // checks if an index is within the tasklist
    bool validateIndex(size_t index) {
      if (index < 0 || index >= tasklist.size()) {
        return false;
      } else {
        return true;
      }
    }
};

#endif // CONTROLLER_H

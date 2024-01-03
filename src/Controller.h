#pragma once

#include "Task.h"

class Controller {
  public:
    // constructor & destructor
    Controller();
    ~Controller();

    // tasklist modification 
    void AddTask(std::string name, std::string description);
    void DeleteTask(int index);

    // tasklist display
    void ShowTask(int index);
    void ShowTasks();

    // tasklist
    std::vector<Task> taskList;
};

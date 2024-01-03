#pragma once

#include "Task.h"

class Controller {
  public:
    // constructor & destructor
    Controller();
    ~Controller();

    // tasklist modification 
    void AddTask(std::string name, std::string description);
    void AddTask(Task task);
    void DeleteTask(int index);
    void ClearTaskList();

    // tasklist display
    void ShowTask(int index);
    void ShowTask(Task task);
    void ShowTasks();

    // getting task references
    Task* GetTask(int index);

    // tasklist
    std::vector<Task> taskList;
    std::string file;
};

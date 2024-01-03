#include "Controller.h"
#include <iostream>
#include <vector>

Controller::Controller() {
  taskList.clear();
}

Controller::~Controller() {
  taskList.clear();
}

void Controller::AddTask(std::string name = "", std::string description = "") {
  // instantiate new task and push to taskList
  taskList.emplace_back(Task(name, description));
}

void Controller::DeleteTask(int index) {
  // check if index is valid
  if (index < 0 && index >= taskList.size()) {
    return;
  }

  // remove task at index
  taskList.erase(taskList.begin() + index);
}

void Controller::ShowTask(int index) {
  // check if index is valid
  if (index < 0 && index >= taskList.size()) {
    return;
  }

  // display task at index
  std::cout << index << ". " << taskList[index].GetInfo() << "\n";
}

void Controller::ShowTasks() {
  // iterate through taskList and show each task
  for (int i = 0; i < taskList.size(); ++i) {
    ShowTask(i);
  }
}

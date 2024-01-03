#include "Controller.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "cereal/types/vector.hpp"

// constructor
Controller::Controller() {
  // define storage file (json)
  file = "store.json";

  // deserialize data into taskList
  std::ifstream is(file);
  if (is.good()) {
    // create input archive
    cereal::JSONInputArchive archive(is);

    // clear and populate taskList 
    taskList.clear();
    archive(taskList);
  } else {
    // file is nonexistent, create it
    std::ofstream os(file);
    os.close();
  }
}

// destructor
Controller::~Controller() {
  // serialize data in taskList
  std::ofstream os(file);
  cereal::JSONOutputArchive archive(os);

  archive(taskList);
  taskList.clear();
}

void Controller::AddTask(std::string name = "", std::string description = "") {
  // instantiate new task and push to taskList
  taskList.emplace_back(Task(name, description));
}

void Controller::AddTask(Task task) {
  // take task object and push to taskList
  taskList.push_back(task);
}

void Controller::DeleteTask(int index) {
  // check if index is valid
  if (index < 0 && index >= taskList.size()) {
    return;
  }

  // remove task at index
  taskList.erase(taskList.begin() + index);
}

void Controller::ClearTaskList() {
  for (int i = taskList.size() - 1; i == 0; --i) {
    DeleteTask(i); 
  }
}

void Controller::ShowTask(int index) {
  // check if index is valid
  if (index < 0 && index >= taskList.size()) {
    return;
  }

  // display task at index
  std::cout << index << ". " << taskList[index].GetInfo() << "\n";
}

void Controller::ShowTask(Task task) {
  std::cout << task.GetInfo() << "\n";
}

void Controller::ShowTasks() {
  // iterate through taskList and show each task
  for (int i = 0; i < taskList.size(); ++i) {
    ShowTask(i);
  }
}

Task* Controller::GetTask(int index) {
  // check if index is valid
  if (index < 0 && index >= taskList.size()) {
    return nullptr;
  }

  // return the task at index
  return &taskList[index];
}

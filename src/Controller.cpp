#include "Controller.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "cereal/types/vector.hpp"

// constructor
Controller::Controller() {
  // define storage file (json)
  file = "store.json";

  // try to deserialize data into taskList
  try {
    std::ifstream is(file);
    if (is.good()) {
      // create input archive
      cereal::JSONInputArchive archive(is);

      // clear and populate taskList 
      taskList.clear();
      archive(taskList);
    }
  }
  catch (cereal::RapidJSONException& e) {
    // file is empty / doesn't exist
    taskList.clear(); 
    std::ofstream os(file);
    os.close(); 
  }
}

// destructor
Controller::~Controller() {
  // serialize data in taskList
  std::ofstream os(file);
  cereal::JSONOutputArchive archive(os);

  // depopulate tasklist and clear
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

bool Controller::DeleteTask(size_t index) {
  // check if index is valid  
  if (validateIndex(index)) {
    // remove task at index
    taskList.erase(taskList.begin() + index);
    return true;
  } else {
    // index was invalid, print error
    std::cerr << "Passed index '" << index << "' is out of range.\n";
    return false;
  }
}

void Controller::ClearTaskList() {
  taskList.clear();
}

void Controller::ShowTask(size_t index) {
  // check if index is valid
  if (validateIndex(index)) {
    // display task at index
    std::cout << index << ". " << taskList.at(index).GetInfo() << "\n";
  } else {
    // index was invalid, print error
    std::cerr << "Passed index '" << index << "' is out of range.\n";
  }
}

void Controller::ShowTasks() {
  // iterate through taskList and show each task
  for (size_t i = 0; i < taskList.size(); ++i) {
    ShowTask(i);
  }
}

std::vector<std::tuple<int, Task>> Controller::SearchTasks(std::string search) {
  std::vector<std::tuple<int, Task>> tVec;

  // iterate through tasklist and check if Task.name or Task.description match
  for (size_t i = 0; i < taskList.size(); ++i) {
    Task task = taskList[i];
    if (task.getName() == search || task.getDescription() == search) {
      tVec.emplace_back(std::make_tuple(i, task));
    }
  }

  return tVec;
}

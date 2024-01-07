#include "Controller.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "cereal/types/vector.hpp"

// constructor
Controller::Controller() {
  // define storage file (json)
  file = "store.json";

  // try to deserialize data into tasklist
  try {
    std::ifstream is(file);
    if (is.good()) {
      // create input archive
      cereal::JSONInputArchive archive(is);

      // clear and populate tasklist
      tasklist.clear();
      archive(tasklist);
    }
  }
  catch (cereal::RapidJSONException& e) {
    // file is empty / doesn't exist
    tasklist.clear(); 
    std::ofstream os(file);
    os.close(); 
  }
}

// destructor
Controller::~Controller() {
  // serialize data in tasklist
  std::ofstream os(file);
  cereal::JSONOutputArchive archive(os);

  // depopulate tasklist and clear
  archive(tasklist);
  tasklist.clear();
}

bool Controller::AddTask(std::string name, std::string description) {
  // instantiate new task and push to tasklist
  if (name == "") {
    return false;
  }
  tasklist.emplace_back(Task(name, description));
  return true;
}

bool Controller::DeleteTask(size_t index) {
  // check if index is valid  
  if (validateIndex(index)) {
    // remove task at index
    tasklist.erase(tasklist.begin() + index);
  } else {
    // index was invalid, print error
    std::cerr << "Passed index '" << index << "' is out of range.\n";
    return false;
  }
  return true;
}

bool Controller::EditTask(int index, std::string nd, std::string value) { 
  if (validateIndex(index)) {
    if (nd == "name") {
      tasklist.at(index).setName(value);
    } else {
      tasklist.at(index).setDescription(value);
    } 
  } else {
    // index was invalid, print error
    std::cerr << "Passed index '" << index << "' is out of range.\n";
    return false;
  }
  return true; 
}

void Controller::ClearTasklist() {
  tasklist.clear();
}

void Controller::ShowTask(size_t index) {
  // check if index is valid
  if (validateIndex(index)) {
    // display task at index
    std::cout << index << ". " << tasklist.at(index).GetInfo() << "\n";
  } else {
    // index was invalid, print error
    std::cerr << "Passed index '" << index << "' is out of range.\n";
  }
}

bool Controller::ShowTasks() {
  if (tasklist.size() == 0) {
    return false;
  }

  // iterate through tasklist and show each task
  for (size_t i = 0; i < tasklist.size(); ++i) {
    ShowTask(i);
  }
  return true;
}

std::vector<std::tuple<int, Task>> Controller::SearchTasks(std::string search) {
  std::vector<std::tuple<int, Task>> tVec;

  // iterate through tasklist and check if Task.name or Task.description match
  for (size_t i = 0; i < tasklist.size(); ++i) {
    Task task = tasklist[i];
    if (task.getName() == search || task.getDescription() == search) {
      tVec.emplace_back(std::make_tuple(i, task));
    }
  }

  return tVec;
}

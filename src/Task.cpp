#include "Task.h"
#include <iostream>

// default constructor
Task::Task(std::string name, std::string description) {
  this->name = name;
  this->description = description;
}

std::string Task::GetInfo() {
  return this->name + "\n" + this->description + "\n";
}

std::string Task::getName() {
  return name;
}

void Task::setName(std::string name) {
  this->name = name;
}

std::string Task::getDescription() {
  return description;
}

void Task::setDescription(std::string description) {
  this->description = description;
}

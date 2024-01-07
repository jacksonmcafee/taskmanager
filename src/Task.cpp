#include "Task.h"
#include <iostream>

// default constructor
Task::Task(std::string name, std::string description) {
  this->name = name;
  this->description = description;
}

std::string Task::GetInfo() {
  if (this->description == "") { return this->name; }
  else { return this->name + " - " + this->description; }
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

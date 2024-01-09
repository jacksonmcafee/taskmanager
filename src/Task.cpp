#include "Task.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// default constructor
Task::Task(std::string name, std::string description, std::chrono::system_clock::time_point due_date) {
  this->name = name;
  this->description = description;
  this->due_date = due_date;
}

std::string Task::GetInfo() {
  std::string str = "";
  str += formatDate(due_date) + " ";
  str += name;
  str += (description == "") ? "" : " - " + description;
  return str;
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

std::chrono::system_clock::time_point Task::getDueDate() {
  return due_date;
}

void Task::setDueDate(std::chrono::system_clock::time_point due_date) {
  this->due_date = due_date;
}

std::string Task::formatDate(std::chrono::system_clock::time_point date) {
  // convert time_point to tm structure
  std::time_t time = std::chrono::system_clock::to_time_t(date);
  std::tm timeInfo = *std::localtime(&time);

  // format the date as a string
  std::ostringstream dateString;
  dateString << std::setfill('0') << std::setw(2) << timeInfo.tm_mon + 1 << '/'
             << std::setw(2) << timeInfo.tm_mday << '/'
             << std::setw(2) << (timeInfo.tm_year % 100);  

  return dateString.str();
}

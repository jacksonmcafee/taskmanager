#pragma once

#include <string>

class Task {
  public:
    // constructor
    Task(std::string name = "No Name", std::string description = "No Description");

    // show task
    std::string GetInfo();

    // getters and setters
    std::string getName();
    void setName(std::string name);

    std::string getDescription();
    void setDescription(std::string description);

  private:
    std::string name;
    std::string description;
};

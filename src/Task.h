#pragma once

#include <string>
#include "cereal/archives/json.hpp"
#include "cereal/types/string.hpp"

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
 
    template <class Archive>
    void serialize(Archive& archive) {
      archive(this->name, this->description);
    }

  private:
    std::string name;
    std::string description;
};

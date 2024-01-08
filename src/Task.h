#ifndef TASK_H
#define TASK_H

#include <string>
#include "cereal/archives/json.hpp"
#include "cereal/types/string.hpp"

class Task {
  public:
    // constructor
    Task(std::string name = "", std::string description = "");

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

#endif // TASK_H

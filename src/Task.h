#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>
#include "cereal/archives/json.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/chrono.hpp"

class Task {
  public:
    // constructor
    Task(std::string name = "", std::string description = "", std::chrono::system_clock::time_point date = std::chrono::system_clock::now());

    // show task
    std::string GetInfo();

    // getters and setters
    std::string getName();
    void setName(std::string name);
  
    std::string getDescription();
    void setDescription(std::string description);
 
    std::chrono::system_clock::time_point getDate();
    void setDate(std::chrono::system_clock::time_point date);

    template <class Archive>
    void serialize(Archive& archive) {
      archive(name, description, date);
    }

  private:
    // helper function to convert a time_point to a string
    std::string formatDate(std::chrono::system_clock::time_point date); 

    std::string name;
    std::string description;
    std::chrono::system_clock::time_point date;
};

#endif // TASK_H

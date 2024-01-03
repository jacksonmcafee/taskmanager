#include "Controller.h"

int main() {
  Controller controller;
  
  controller.ShowTasks();

  controller.ClearTaskList();

  controller.ShowTasks();
  return 0;
}

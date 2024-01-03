#include "Controller.h"

int main() {
  Controller controller;

  controller.AddTask("New Task", "New Description");
  controller.AddTask("Other Task", "Other Description");

  controller.ShowTasks();

  controller.DeleteTask(1);

  controller.ShowTasks();

  return 0;
}

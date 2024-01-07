# taskmanager

taskmanager is a basic task-tracking CLI tool. 


## Usage/Examples
Currently, it supports single-command mode and interactive mode, as shown below.

### Single-command Mode
```bash
./taskmanager add "Make granola" "Make strawberry/banana granola for Sarah"
./taskmanager list
./taskmanager edit 0 name "Make Sarah granola"
```

- The first call creates a task with the name "Make Granola" and the description "Make strawberry... for Sarah". It then exits the program.
- The second call lists all the existing tasks. It then exits the program. 

This is recommended for quick access (modifying single tasks, seeing current tasks, etc.)

### Interactive Mode
```bash
./taskmanager
add "Make Granola" "Make strawberry/banana granola for Sarah"
list
edit 0 name "Make Sarah granola"
quit
```

- The first call enters the taskmanager's interactive mode. Each subsequent command is handled within the flow of the program until the `quit` command is reached. 
- It achieves the same result as the single-command flow, but is slightly less verbose and only requires a single instantiation of the taskmanager. 

This is recommended for multiple additions/deletions/edits of tasks or more complex visualization of tasks. 
## Authors

- [@jacksonmcafee](https://www.github.com/jacksonmcafee)


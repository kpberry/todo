Command line todo list manager.

Building: 
    cmake .
    make

Use:
    ./todo -p <project name> <<other flags>>

Flags: 
    -p <project name>      specifies a project on which an action should be performed
    -t <task number>       specifies a task number on which an action should be performed
    
    -m <string>            specifies a message when creating a task

    -n                     advances a task to the next stage 
    -u                     resets a task to the previous stage (undo)
    -s <status code>       sets the status of a task 

    -c <status code>       clears all tasks in a project with the specified status code
    -d <task or project>   deletes the specified task or project

Examples:
    // Add a task to the Shopping project with the text "Remember to buy eggs"
    ./todo -p Shopping -m "Remember to buy eggs" 
    // Advance the first task in shopping to the "started" stage
    ./todo -p Shopping -t 1 -n
    ./todo -p Shopping -m "Remember to buy bread"
    // Set both taks in the Shopping project to "complete"
    ./todo -p Shopping -s c -t 1
    ./todo -p Shopping -s c -t 2
    // Clear all completed tasks from the Shopping project
    ./todo -p Shopping -c c

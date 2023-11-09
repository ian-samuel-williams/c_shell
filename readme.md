This program is a recreation of a shell program written in C. 

The program enters a loop, reallocates an array to take user input, 
tokenizes this input and then executes this input through forking. 
The command is run in the child while the parent waits until the child is 
complete. 

If the user inputs "exit", the shell is terminated and the memory is 
freed.

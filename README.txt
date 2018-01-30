/**********************************
 * File: my_shell.c
 * Author: Vicky Mohammad
 * ID: 0895381
 * Email: mohammav@uoguelph.ca
 * Date: 2018
 * Brief: a basic shell
 *********************************/

*************** My Algorithm *************** 
For my program, I created myCode function to seperate the rest of the code
that the prof provided to make things easier. Firstly I used an infinite loop
until the user enter the "exit" command on the program shell on an if statement
using strcmp function to compare the args as well as other arguments. I created
an function that execute the arguments called executeArgs to make my coding
a lot easer, the executeArgs() is where I fork a new child process and run the 
arguments, through the execvp(). Through the loop I put the function where
I compare the argments string with if statement, such as the adding command
and argument counter. For the process 

****************** Assumption ****************** 
- The brief report has been written in the readme.txt since it does not
  say specify in the assignment.

****************** Custom Command: subtract ****************** 
For my custom command, the argument is called when calling the argument
"subtract" similarly to the "add" argument, this essentially will subtract
the numbers such "subtract 10 5" which output 10 - 5 = 5. 

****************** Bonus command:  ******************  
For the bonus mark, I recreated "cd" function which will act exactlly like the
cd arguments similarly to shell commands. To use the "cd" simply write
"cd .." to go back or to go to the folder, write the folder name after the 
cd commad. 

*********** Compilation ************ 
Running the programs(s)  go to program file
type "make" on the command terminal, and then type "./msh"
to run the program.
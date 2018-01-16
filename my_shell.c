//import lib
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
//macro
#define DEBUG true

//prof func
extern char **getln();

int searchArgs(char** args, const char* stringToBeSearched, int arraySize){
	int foundString = -1;
	for(int x=0; x<arraySize; x++){
		if(strcmp(args[x], stringToBeSearched) == 0){
			foundString++;
		}//end if
	}//end for
	return foundString;
}//end if

void fileOpen(char** string, int argNum){
	int foundOutput = 0;
	int foundInput = 0;

	if(string[2] == '>'){
		
	}else if(string[2] == '<'){

	}//end if
}//end func

void exitCommand(char* string, int argNum){
	if(strcmp(string, "exit") == 0 && argNum == 0){
		exit(0);
	}//end if
}//end func

void myCode(char** args, int argNum){
	exitCommand(args[0], argNum);
	pid_t child_pid;
	int statLock;

	child_pid = fork();
	if(child_pid == 0){
		//child
		execvp(args[0], args);
		exit(0);
	}else{
		//parents
		waitpid(child_pid, &statLock, WUNTRACED);
	}//end if
}//end func

int main() {
	//dec prof var
	int i;
	char **args; 
	//my var
	int argNum = -1;
	
	//infinite program
	while(1) {
		argNum = 0;
		args = getln();
		for(i = 0; args[i] != NULL; i++) {
			printf("Argument %d: %s\n", i, args[i]);
			argNum++;
		}//end for

		//my code
		myCode(args, argNum);
	}//end while

	//exit
	return 0;
}//end main


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
	//program search through the args
	int foundString = 0;
	int foundAtIndex = -1;
	for(int x=0; x<arraySize; x++){
		if(strcmp(args[x], stringToBeSearched) == 0){
			foundAtIndex = x;
			foundString++;
			if(foundString >= 2){
				return -2;
			}//end if
		}//end if
	}//end for
	return foundAtIndex;
}//end if

void fileCommand(char** args, int argNum){
	//dec vars
	FILE* filePointer;
	int outputIndex = searchArgs(args, ">", argNum+1);
	int inputIndex = searchArgs(args, "<", argNum+1);
	//debug
	if(DEBUG)printf("outputIndex: %d", outputIndex);
	if(DEBUG)printf("inputIndex: %d", inputIndex);
	//check if there us input or output
	if(outputIndex >= 0 && inputIndex >= 0){
		printf("Invalid argument, cannot take '>' and '<' at the same time\n");
	}else if(outputIndex >= 0){
		filePointer = freopen(args[outputIndex+1], "w+", stdout);
		fclose(filePointer);
	}else if(inputIndex >= 0){
		filePointer = freopen(args[inputIndex+1], "r", stdout);
		fclose(filePointer);
	}else if(outputIndex == -2){
		printf("Invalid argument, found multiple '>' command");
	}else if(inputIndex == -2){
		printf("Invalid argument, found multiple '<' command");
	}//end if
}//end func

void exitCommand(char* arg, int argNum){
	if(strcmp(arg, "exit") == 0 && argNum == 0){
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


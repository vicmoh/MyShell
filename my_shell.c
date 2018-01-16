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
			if(DEBUG)printf("Found %d match arg\n", foundString);
			if(foundString >= 2){
				return -2;//when multiple match
			}//end if
		}//end if
	}//end for
	return foundAtIndex;
}//end if

void fileCommand(char** args, int numOfArg){
	//dec vars
	FILE* filePointer;
	int outputIndex = searchArgs(args, ">", numOfArg);
	int inputIndex = searchArgs(args, "<", numOfArg);
	//debug
	if(DEBUG)printf("outputIndex: %d\n", outputIndex);
	if(DEBUG)printf("inputIndex: %d\n", inputIndex);
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
		printf("Invalid argument, found multiple '>' command\n");
	}else if(inputIndex == -2){
		printf("Invalid argument, found multiple '<' command\n");
	}//end if
}//end func

void exitCommand(char* arg, int numOfArg){
	if(strcmp(arg, "exit") == 0 && numOfArg == 1){
		exit(0);
	}//end if
}//end func

void myCode(char** args, int numOfArg){
	//commands
	exitCommand(args[0], numOfArg);
	fileCommand(args, numOfArg);

	//forking
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
	int numOfArg = 0;
	
	//infinite program
	while(1) {
		numOfArg = 0;
		args = getln();
		for(i = 0; args[i] != NULL; i++) {
			printf("Argument %d: %s\n", i, args[i]);
			numOfArg++;
		}//end for

		//my code
		myCode(args, numOfArg);
	}//end while

	//exit
	return 0;
}//end main


/**
 * Name: Vicky Mohammad
 * ID: 0895381
 * Email: mohammav@gmail.com
 */

/**********************************************
 * LIBRARY
 **********************************************/

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
#include <stdbool.h>
#include <signal.h>
//macro
#define DEBUG true
#define CHECK printf("CHECK\n")

/**********************************************
 * HEADERS
 **********************************************/

extern char **getln();
void myCode(char** args, int numOfArg);
int searchArgs(char** args, const char* stringToBeSearched, int arraySize);
void executeArgs(char** args, int numOfArg);
bool exitCommand(char* arg, int numOfArg);
bool newCommands(char** args, int numOfArg);
void stop(int sig);

/**********************************************
 * CODES
 **********************************************/

int main() {
	//dec prof var
	int i;
	char **args; 
	int numOfArg = 0;
	//print to let user know that shell started
	printf("Starting shell...\n");

	//infinite program
	while(1) {
		//command print
		printf("> ");

		numOfArg = 0;
		args = getln();
		for(i = 0; args[i] != NULL; i++) {
			if(DEBUG)printf("Argument %d: %s\n", i, args[i]);
			numOfArg++;
		}//end for

		//my code
		myCode(args, numOfArg);
	}//end while

	//exit
	return 0;
}//end main

void myCode(char** args, int numOfArg){
	//dec vars
	int x = 0;

	//this code is going on a loop
	//which goes through the program and check the command
	//on the if statement
	if(numOfArg > 0){
		if(exitCommand(args[0], numOfArg)){
			if(DEBUG)printf("Error: Exit program failed\n");
		}else if(newCommands(args, numOfArg)){
			if(DEBUG)printf("Other command sucess\n");
		}else if(args[x+1] == NULL){
			//if there is no argmuent
			executeArgs(args, numOfArg);
		}else if(args[x+1] != NULL){
			//if there is more than one argumment
			executeArgs(args, numOfArg);
		}//end if
	}//end if
}//end func

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

void executeArgs(char** args, int numOfArg){
	//dec vars
	const int nextArg = 1; 
	int x = 0, y = 0;
	char** argv = malloc(sizeof(char*)*256);
	//dec for the file input and ouput and background
	int inputIndex = -1, outputIndex = -1, status = 0, sortIndex = 0;
	char fileName[256];
	//FILE* file = NULL;
	//dec for the arguemnts
	argv[x] = args[y];
	argv[x+nextArg] = args[y+nextArg];
	argv[x+2] = NULL;
	//for the andpercent background process
	int iterate = 1;
	int sig = -1;

	//loop through unti andpercent found
	while(args[iterate] != NULL){
		if(strcmp(args[iterate],"&") == 0){
			//remove the andpercent and set the sig to 1
			sig = 1;
			args[iterate] = NULL;
		}//end if
		iterate++;
	}//end for
	
	//if sigset is 1, run the sigset to the background
	if (sig == 1){
		sigset(SIGCHLD, stop);
	}//end if
	
	int inputExist = -1;
	int outputExist = -1;
	bool foundBoth = false;
	inputExist = searchArgs(args, "<", numOfArg);
	outputExist = searchArgs(args, ">", numOfArg);
	if(inputExist > 0 && outputExist > 0){
		foundBoth = true;
	}else{
		foundBoth = false;
	}//end if
	if(DEBUG)printf("foundBoth: %d\n", foundBoth);

	bool singleInput = false;
	bool singleOutput = false;
	char* bufferFileName;CHECK;
	if(foundBoth == false){CHECK;
		for(int x=0; args[x] != NULL; x++){
			if(strcmp(args[x], ">") == 0){
				singleOutput = true;
				bufferFileName =  args[x+1];
				args[x+1] = NULL;
				args[x] = NULL;
			}//end if
			if(strcmp(args[x], "<") == 0){
				singleInput = true;
				bufferFileName = args[x+1];
				args[x+1] = NULL;
				args[x] = NULL;
			}//end if
		}//end if
	}//end if
	CHECK;

	//fork a new process
	pid_t pid = fork();
	if(pid == 0){
		//see if there is more than one arguments
		if(foundBoth == true){
			//search the arg and get the index
			inputIndex = searchArgs(args, "<", numOfArg);
			outputIndex = searchArgs(args, ">", numOfArg);
			if(DEBUG)printf("outputIndex: %d\n", outputIndex);
			if(DEBUG)printf("inputIndex: %d\n", inputIndex);

			//for the inputs 
			if(inputIndex > 0){
				strcpy(fileName, args[inputIndex+1]);
				if(DEBUG)printf("fileName: %s\n", fileName);
				freopen(fileName, "r", stdin);
				printf("Reading...");
			}//end if
			//for the output
			if(outputIndex > 0){
				strcpy(fileName, args[outputIndex+1]);
				if(DEBUG)printf("fileName: %s\n", fileName);
				freopen(fileName, "w+" , stdout);
				printf("Writing...\n");
			}//end if
		}else if(foundBoth == false){
			if(DEBUG)printf("Went to one arrow arg \n");
			//when there is only single argument
			if(singleOutput == true){
				freopen(bufferFileName, "w+" , stdout);
			}//end if
			if(singleInput == true){
				freopen(bufferFileName, "r", stdin);
			}//end if
		}//end if

		//child process works 
		int execResult = execvp(argv[x], argv);
		if(execResult >= 0){
			execvp(argv[x], argv);
		}else if(execResult < 0){
			printf("Invalid argument, please re-enter\n");
			exit(1);
		}//end if
	}else if(pid){
		//thee praent or the original process
		wait(&status);
	}else if(pid < 0){
		//there is an error
		printf("Error: failed to created a new process\n");
		exit(0);
	}//end if

	//free the memory
	free(argv);
}//end dif

bool exitCommand(char* arg, int numOfArg){
	if(strcmp(arg, "exit") == 0 && numOfArg == 1){
		printf("Exiting shell...\n");
		exit(0);
		return true;
	}//end if
	return false;
}//end func

bool newCommands(char** args, int numOfArg){
	//other commnads for question number 2
	if(strcmp("add", args[0]) == 0){
		//dec nedded vars
		char* stringNum = malloc(sizeof(char*)*256);
		char* printString = malloc(sizeof(char*)*256);
		int total = 0;
		int num = 0;
		//loop and add the number
		for(int x = 1; x < numOfArg; x++){
			//conver the number and save it to the stringNum
			stringNum = args[x];
			if(DEBUG)printf("adding number: %s\n", stringNum);
			strcat(printString, args[x]);
			if(x != numOfArg-1){
				strcat(printString, " + ");
			}//end if
			num = strtol(stringNum, NULL, 0);
			total+= num;
		}//end if
		printf("%s = %d\n", printString, total);
		free(stringNum);
		free(printString);
		return true;
	}else if(strcmp("arg", args[0]) == 0){
		//dec for needed variables
		int argc = numOfArg -1;
		char* argString = malloc(sizeof(char*)*256);
		//loop and add the string for the argument
		for(int x = 1; x <= argc; x++){
			strcat(argString, args[x]);
			strcat(argString, " ");
		}//end for
		printf("argc = %d, args = %s\n", argc, argString);
		free(argString);
		return true;
	}else if(strcmp("subtract", args[0]) == 0){
		//dec nedded vars
		char* stringNum = malloc(sizeof(char*)*256);
		char* printString = malloc(sizeof(char*)*256);
		int total = 0;
		int num = 0;
		//loop and add the number
		for(int x = 1; x < numOfArg; x++){
			//conver the number and save it to the stringNum
			stringNum = args[x];
			if(DEBUG)printf("adding number: %s\n", stringNum);
			strcat(printString, args[x]);
			if(x != numOfArg-1){
				strcat(printString, " - ");
			}//end if
			num = strtol(stringNum, NULL, 0);
			total-= num;
		}//end if
		printf("%s = %d\n", printString, total);
		free(stringNum);
		free(printString);
		return true;
	}//end if
	return false;
}//end func

void stop(int sig){
	int status;
  	wait(&status);
	printf("Process is done\n");
}//end func

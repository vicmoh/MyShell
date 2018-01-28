/**********************************************
 * Name: Vicky Mohammad
 * ID: 0895381
 * Email: mohammav@gmail.com
 **********************************************/

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
//macro
#define DEBUG true

/**********************************************
 * HEADERS
 **********************************************/

extern char **getln();
void myCode(char** args, int numOfArg);
int searchArgs(char** args, const char* stringToBeSearched, int arraySize);
void executeArgs(char** args);
bool exitCommand(char* arg, int numOfArg);
bool fileCommand(char** args, int numOfArg);
bool addCommand(char** args, int numOfArg);

/**********************************************
 * CODES
 **********************************************/

int main() {
	//dec prof var
	int i;
	char **args; 
	//my var
	int numOfArg = 0;

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
	if(exitCommand(args[0], numOfArg)){

	}else if(fileCommand(args, numOfArg)){
	
	}else if(addCommand(args, numOfArg)){
	
	}else if(args[x+1] == NULL){
		//if there is noa argmuent
		executeArgs(args);
	}else if(args[x+1] != NULL){
		//if there is more than one argumment
		executeArgs(args);
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

void executeArgs(char** args){
	//dec vars
	int x = 0, y = 0;
	char** argv = malloc(sizeof(char*)*256);
	argv[x] = args[y];
	argv[x+1] = args[y+1];
	argv[x+2] = NULL; //set the end with null

	//fork a new process
	pid_t pid = fork();
	if(pid < 0){
		//there is an error
		printf("Error: failed to created a new process\n");
		exit(1);
	}else if(pid > 0){
		//thee praent or the original process
		wait(NULL);
	}else if(pid == 0){
		//child process works 
		int execResult = execvp(argv[x], argv);
		if(execResult < 0){
			printf("Error: execvp failed\n");
			exit(1);
		}else{
			execvp(argv[x], argv);
		}//end if
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

bool fileCommand(char** args, int numOfArg){
	//dec vars
	FILE* filePointer;
	int outputIndex = searchArgs(args, ">", numOfArg);
	int inputIndex = searchArgs(args, "<", numOfArg);

	//debug
	if(DEBUG)printf("outputIndex: %d\n", outputIndex);
	if(DEBUG)printf("inputIndex: %d\n", inputIndex);
	//check if there us input or output
	if(outputIndex >= 0){
		//for the > wirting the stuff to the created file
		if(DEBUG)printf("args[outputIndex+1]: %s\n", args[outputIndex+1]);
		args[outputIndex] = NULL;
		filePointer = freopen(args[outputIndex+1], "w+", stdout);
		fclose(filePointer);
	}else if(inputIndex >= 0){
		filePointer = freopen(args[inputIndex+1], "r", stdout);
		fclose(filePointer);
	}//end if
	return false;
}//end func

bool addCommand(char** args, int numOfArg){
	if(strcmp("add", args[0]) == 0){
		//loop and add the number
		char* stringNum = malloc(sizeof(char*)*256);
		char* printString = malloc(sizeof(char*)*256);
		int total = 0;
		int num = 0;
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
	}//end
	return false;
}//end func
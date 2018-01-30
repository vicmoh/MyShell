/**
 * @file my_shell.c
 * @author Vicky Mohammad
 * @id 0895381
 * @email mohammav@uoguelph.ca
 * @date 2018
 * @brief a basic shell
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
#define DEBUG false
#define CHECK printf("CHECK\n")

int listOfProcess[99];
int countProcess = 0;

/**********************************************
 * HEADERS
 **********************************************/

/**
 * program gets the line to the to the string array
 * @return string array
 */
extern char **getln();

/**
 * a function that malloc a new memory
 * and set the char with the new string
 * @param string of to be set
 * @return string array
 */
char* setString(char* string);

/**
 * a function for all my code to seperate it
 * from the prof
 * @param args for the arg array
 * @param numOfArg
 */
void myCode(char** args, int numOfArg);

/**
 * a search args function that search the argument
 * and return the index
 * @param args
 * @param stringToBeSearched
 * @arraySize
 * @return the index of the arg being searched 
 */
int searchArgs(char** args, const char* stringToBeSearched, int arraySize);

/**
 * a function tha forks and creates a new child process
 * @param args
 * @param numOfArgs
 */
void executeArgs(char** args, int numOfArg);

/**
 * a function that exit the commands
 * @param arg
 * @numOfArg
 * @return ture when it exits, return false when it does not exit
 */
bool exitCommand(char* arg, int numOfArg);

/**
 * a functions for the other commands such as add and etc
 * @param args
 * @param nummOfArg
 * @return true if arg works, false if it failed
 */
bool newCommands(char** args, int numOfArg);

/**
 * a dummy function that is used for the & ampersands
 * @param dummy int
 */
void stop(int ampersand);

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

char* setString(char* string){
    char* newString = calloc(1 ,sizeof(char*)*(strlen(string)+9));
    strcpy(newString, string);
    return newString;
}//end func

void myCode(char** args, int numOfArg){
	//this code is going on a loop
	//which goes through the program and check the command
	//on the if statement
	if(numOfArg > 0){
		if(exitCommand(args[0], numOfArg)){
			if(DEBUG)printf("Error: Exit program failed\n");
		}else if(newCommands(args, numOfArg)){
			if(DEBUG)printf("Other command sucess\n");
		}else{
			//if there is no argmuent
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
	int x = 0;
	//dec for the file input and ouput and background
	int inputIndex = 0, outputIndex = 0, ampersand = 0, waitTime = 0;
	char* fileName;
	
	//to check if there is double arg
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

	//check the < > &
	inputIndex = searchArgs(args, "<", numOfArg);
	outputIndex = searchArgs(args, ">", numOfArg);
	if(foundBoth == false){
		for(int x=0; args[x] != NULL; x++){
			if(strcmp(args[x], ">") == 0){
				fileName = setString(args[x+1]);
				args[x+1] = NULL;
				args[x] = NULL;
				break;
			}//end if
		}//end for
		for(int x=0; args[x] != NULL; x++){
			if(strcmp(args[x], "<") == 0){
				fileName = setString(args[x+1]);
				args[x+1] = NULL;
				args[x] = NULL;
				break;
			}//end if
		}//end for
		for(int x=0; args[x] != NULL; x++){
			if(strcmp(args[x], "&") == 0){
				//remove the ampersand and set the ampersand to 1
				ampersand = 1;
				args[x] = NULL;
				printf("Process is done\n");
				return;
			}//end if
		}//end for
	}//end if
	//if ampersandset is 1, run the ampersandset to the background
	if (ampersand == 1){
		if(DEBUG)printf("sigset is called\n");
		signal (SIGCHLD, stop);
	}//end if*/

	//fork a new process
	pid_t pid = fork();
	if(DEBUG)printf("forked\n");
	listOfProcess[countProcess] = pid;
	countProcess++;

	//check the process
	if(pid == 0){
		//see if there is more than one arguments
		if(foundBoth == true){
			//search the arg and get the index
			inputIndex = searchArgs(args, "<", numOfArg);
			outputIndex = searchArgs(args, ">", numOfArg);
			if(DEBUG)printf("outputIndex: %d\n", outputIndex);
			if(DEBUG)printf("inputIndex: %d\n", inputIndex);

			//check the input and outout filename
			if(outputIndex > 0){
				fileName = setString(args[outputIndex+1]);
				args[outputIndex+1] = NULL;
				if(DEBUG)printf("fileName: %s\n", fileName);
				freopen(fileName, "w+" , stdout);
				printf("Writing...\n");
			}//end if
			//for the inputs 
			if(inputIndex > 0){
				fileName = setString(args[inputIndex+1]);
				args[inputIndex+1] = NULL;
				if(DEBUG)printf("fileName: %s\n", fileName);
				freopen(fileName, "r", stdin);
				printf("Reading...\n");
			}//end if
			//for the output
		}else if(foundBoth == false){
			if(DEBUG)printf("Went to one arrow arg \n");
			//when there is only single argument
			if(outputExist > 0){
				if(DEBUG)printf("foundboth writting...\n");
				freopen(fileName, "w+" , stdout);
			}//end if
			if(inputExist > 0){
				if(DEBUG)printf("foundboth reading...\n");
				freopen(fileName, "r", stdin);
			}//end if
		}//end if*/

		//child process works 
		if(DEBUG)printf("execvp arg value: %s\n", args[x]);
		int execResult = execvp(args[0], args);
		if(execResult >= 0){
			execvp(args[x], args);
		}else if(execResult < 0){
			printf("Error: Execvp failed, Invalid Argument\n");
			exit(1);
		}//end if
	}else if(ampersand == 0){
		//thee parent or the original process
		waitpid(pid, &waitTime, WUNTRACED);
		//wait(&status);
	}else if(pid == -1){
		//there is an error
		printf("Error: failed to created a new process\n");
		exit(0);
	}//end if
}//end dif

bool exitCommand(char* arg, int numOfArg){
	if(strcmp(arg, "exit") == 0 && numOfArg == 1){
		printf("Exiting shell...\n");
		//kill the all child!!
		for(int x=0; x < countProcess; x++){
			kill(listOfProcess[x], SIGKILL);
		}//end if
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
	}else if(strcmp("arg", args[0]) == 0 || strcmp("args", args[0]) == 0){
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
	}else if(strcmp("multiply", args[0]) == 0){
		//dec nedded vars
		char* stringNum = malloc(sizeof(char*)*256);
		char* printString = malloc(sizeof(char*)*256);
		int total = 1;
		int num = 1;
		//loop and add the number
		for(int x = 1; x < numOfArg; x++){
			//conver the number and save it to the stringNum
			stringNum = args[x];
			if(DEBUG)printf("multiply number: %s\n", stringNum);
			strcat(printString, args[x]);
			if(x != numOfArg-1){
				strcat(printString, " x ");
			}//end if
			num = strtol(stringNum, NULL, 0);
			total = total * num;
		}//end if
		printf("%s = %d\n", printString, total);
		free(stringNum);
		free(printString);
		return true;
	}else if(strcmp(args[0], "cd") == 0){
		chdir(args[1]);
		return true;
	}
	return false;
}//end func

void stop(int ampersand){
	int status;
  	wait(&status);
	if(DEBUG)printf("stop function invoked\n");
}//end func
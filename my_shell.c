//import lib
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
//macro
#define DEBUG true

extern char **getln();

void exitFunc(char* string){
	if(strcmp(string, "exit") == 0){
		exit(0);
	}//end if
}//end func



int main() {
	//dec prof var
	int i;
	char **args; 
	int numOfArgs = 0;
	
	//infinite program
	while(1) {
		numOfArgs = 0;
		args = getln();
		for(i = 0; args[i] != NULL; i++) {
			printf("Argument %d: %s\n", i, args[i]);
			//my codes
			numOfArgs++;
		}//end for
		if(DEBUG)printf("numOfArgs: %d\n", numOfArgs);
		if(numOfArgs == 1){
			exitFunc(args[0]);
		}//end if
	}//end while
	return 0;
}//end main


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "fsmFunctions.h"

int main (int argc, char *argv[]) {
	
	testInitialize();
	testRegex();
	testStrParser();
	
	// Check to make sure there are only two inputs 
	if (argc != 3) {
		printf("Incorrect number of command line inputs. Aborting.\n");
		exit(0);
	}
	
	//This array of structs will hold the transitions for the current states. There can be max fifty states. 
	struct states fsmDef[50];
	int transitionCount = 0;
	//Call this function to initialize all transitions to -1. This is how we will tell if a transition is invalid. 
	initialize(fsmDef);
	
	//Call this function to build up the array of structs with the fsm definition from the file input
	transitionCount = interpretFirstFile(fsmDef, argv[1]);	

	printf("FSM has %d transitions\n", transitionCount);
	
	int returnArray[2];
	
	//Call this function to process the fsm input file and print out the transitions
	interpretSecondFile(fsmDef, argv[2], returnArray);      
 	
	printf("after %d steps, state machine finished successfully at state %d\n", returnArray[0], returnArray[1]);

        return 0;
}


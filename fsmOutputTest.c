#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "fsmFunctions.h"

//Will the program fail if there are over 250 input values?
//To test, run fsmOutputTest.c with the files fsmDef.txt and over250.txt
//"fsmOutputTest fsmDef.txt over250.txt"
 
//Will the program fail if there are more than 50 states?
//To test, run fsmOutputTest.c with the files fsmDefOver50.txt and fsmInput.txt
//"fsmOutputTest fsmDefOver50.txt over250.txt"

//Will the program fail if there was an incorrect (not an alphabetic character) input?
//To test, run fsmOutputTest.c with the files fsmDef.txt and fsmInputNotAlpha.txt
//"fsmOutputTest fsmDef.txt fsmInputNotAlpha.txt"

//Will the program fail if no state 0 was provided?
//To test, run fsmOutTest.c with the files fsmDefNoZero.txt and fsmInput.txt
//"fsmOutputTest fsmDefNoZero.txt fsmInput.txt"

//Will the program give the correct output for these input files?
//To test, run fsmOutputTest.c with the files fsmDef.txt and fsmInput.txt
//"fsmOutputTest fsmDef.txt fsmInput.txt:
//Check for this output:
//FSM has 16 transitions
  //at step 0, input a transitions from state 0 to state 1
 // at step 1, input a transitions from state 1 to state 0
  //at step 2, input a transitions from state 0 to state 1
  //at step 3, input a transitions from state 1 to state 0
  //at step 4, input b transitions from state 0 to state 1
  //at step 5, input c transitions from state 1 to state 2
  //at step 6, input b transitions from state 2 to state 1
  //at step 7, input c transitions from state 1 to state 2
//after 8 steps, state machine finished successfully at state 2

void checkExpectedOutput();

int main(int argc, char *argv[]) {
	checkExpectedOutput(argv[1], argv[2]);
	return 0; 
}

void checkExpectedOutput(char *fsmDefFile, char *fsmInput){

        //This function should be, and was, run separately from the main function. It takes preprogrammed input files,
        //so that the programmer can check actual output against expected output
        //it looks similar to the main function, but will take two string arguments instead of command line arguments

        //This array of structs will hold the transitions for the current states. There can be max fifty states.
        struct states fsmDef[50];

	int transitionCount = 0;

        //Call this function to initialize all transitions to -1. This is how we will tell if a transition is invalid.
        initialize(fsmDef);

        //Call this function to build up the array of structs with the fsm definition from the file input
        transitionCount = interpretFirstFile(fsmDef, fsmDefFile);

        printf("FSM has %d transitions\n", transitionCount);

        int returnArray[2];

        //Call this function to process the fsm input file and print out the transitions
        interpretSecondFile(fsmDef, fsmInput, returnArray);

        printf("after %d steps, state machine finished successfully at state %d\n", returnArray[0], returnArray[1]);

        return;

}





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

//This struct will hold the current state and an array of possible transitions, where the index corresponds to the letter's position in the alphabet
struct states {
        int currentState;
        int findNext[26];
};



//This function initializes the array of structs
void initialize(struct states fsmDef[]) {
        //Loop over the 50 possible
        for (int i = 0; i<50; i++){
             //Set the current state attribute to -1;
              fsmDef[i].currentState = -1;
              //Loop over the 26 positions in each array attribute
              for (int j = 0; j < 26; j++) {
                    //Set the next states to -1;
                    fsmDef[i].findNext[j] = -1;
               }
        }
}

int checkRegex(char *currentLine){
        regex_t regex;
        int value;

        //Compile regex to make sure the line of the definition file is in the correct format (integer:character>integer)
        value = regcomp(&regex, "^([0-9]+):[a-zA-Z]>([0-9]+)$", REG_EXTENDED);
        value = regexec(&regex, currentLine, 0, NULL, 0);
        return value;
}

//This functions processes the first input file, the fsm definition, to establish the correct states and transitions within the array of structs
int interpretFirstFile(struct states fsmDef[], char* fileName){
        FILE *fp;
        int ret;
        char line[500];
        int value, counter, currentStateIndex, nextStateInt, index, transitionCount=0, already = 0, already2=0, numberOfStates=0;
        char *strTracker, *input, *nextState, *currentStateInput;
        char delim[] = ":>";

        //Open the fsm definition file
        fp = fopen(fileName , "r");

        //Error checking for failure of file to open
        if (fp == NULL)
            {
              printf("Error! Could not open fsm definition file\n");
              exit(0);
            }

        printf("processing FSM definition file %s\n", fileName);

        //Begin reading the fsm definition file
        while((ret = fscanf(fp," %s ", line)))
        {
           //Break out of the while loop if we've reached the end of the file
           if(ret == EOF)
            {
                break;
            }

           //Throw an error if too many states were included in the transition
           if (numberOfStates > 50){
                printf("Error! Only 50 states are allowed. Aborting.\n");
                exit(0);
           }
            //Add a sentinel to the end of the file line (solved bugs in regex functions and strtok function
            line[strlen(line)] = '\0';

            value = checkRegex(line);

            if (value == REG_NOMATCH){
                printf("Input file in incorrect format. Aborting\n");
                exit(0);
               }

            //Begin parsing the line in the file
            strTracker = strtok(line, delim);

            //The first split will return the current state
            currentStateInput = strTracker;

            counter = 0;

            while (strTracker != NULL)
                {
                counter ++;
                strTracker = strtok(NULL, delim);
                switch (counter) {
                        case 1:
                                //The second split will return the input character
                                input = strTracker;
                                break;
                        case 2:
                                //The third split will return the next state after transition
                                nextState = strTracker;
                                break;
                                }
                }

            //Convert the values into integers to be input in to the array of structs
            currentStateIndex = atoi(currentStateInput);
            int nextStateInt = atoi(nextState);
            index = (int)tolower(input[0]) - 97;

            //Keep track of how many possible transitions are in the fsm definition
            transitionCount++;


            //Loop over the array of structs
            for (int i = 0; i<50; i++){
                //If the state already exists in the definition, then add in the correct transition
                if (fsmDef[i].currentState == currentStateIndex) {
			if (fsmDef[i].findNext[index] != -1) {
				printf("Error. Attempting to redefine previously defined state. Aborting.\n");
				exit(0);
			}
                        fsmDef[i].findNext[index] = nextStateInt;
                        already = 1;
                        break;
                }
            }


            if (already !=1) {
                //If the state does not exist yet, add it into the array of structs and set the transition
                fsmDef[numberOfStates].currentState = currentStateIndex;
                fsmDef[numberOfStates].findNext[index] = nextStateInt;
                //This variable will keep track of how many states have been added
                numberOfStates +=1;
            }

             already = 0;

            //Check to see if a base state of 0 was provided. If it wasn't, throw an error.
            for (int i = 0; i<50; i++){
                if (fsmDef[i].currentState == 0) {
                        already2 = 1;
                        break;
                }
             }
            if (already2!= 1) {
                printf("Error. No base state 0 was provided. Aborting.\n");
		exit(0);
            }
        }

        fclose(fp);
        return transitionCount;
}

//This function processes the second file input, the list of transition inputs, and prints out the transitions and ending state of the fsm
void interpretSecondFile(struct states fsmDef[], char* fileName, int returnArray[]){
        FILE *fp2;
        int ret, currentStateIndex, findNextState;
        char line[500];
        char charLower;

        //Open the file
        fp2 = fopen(fileName, "r");

        int isFirst = 1;

        //Keep track of how many steps are in the fsm
        int stepCounter = 0;

        while((ret = fscanf(fp2," %s ", line)))
        {

         //Check if we've reached the end of the file
         if(ret == EOF)
            {
                break;
            }

        //here check if the input is a single character, otherwise abort
         if (strlen(line) > 1) {
                printf("Incorrect input. Please only input one alphabetic character. Aborting.\n");
                exit(0);
         }
         if (!isalpha(line[0])) {
                printf("Input must be an alphabetic character. Aborting.\n");
                exit(0);
         }

    charLower = tolower(line[0]);

         //If this is the first step, we assume that the machine has started at state 0
        if (stepCounter == 0){
                currentStateIndex = 0;
                for (int i = 0; i<50; i++){
                        //Get the next state given the current state and the input
                        if (fsmDef[i].currentState == currentStateIndex) {
                                findNextState = fsmDef[i].findNext[(int)charLower-97];
                        }
                }
        //If this is not the first step, get the next state given the current state and the input
        } else {
                for (int i = 0; i<50; i++){
                        if (fsmDef[i].currentState == currentStateIndex) {
                                findNextState = fsmDef[i].findNext[(int)charLower-97];
                        }
                }
        }

        //If the proposed next state is equal to -1, then we know this is not a vald transition
        if (findNextState == -1){
                printf("Invalid transition. Aborting.\n");
                exit(0);
          }

        printf("  at step %d, input %c transitions from state %d to state %d\n", stepCounter, line[0], currentStateIndex, findNextState);
        stepCounter++;

        //Error checking for a maximum of 250 inputs
        if (stepCounter > 250) {
                printf("Error. Too many inputs. Aborting.\n");
                exit(0);
        }

        currentStateIndex = findNextState;
        }

     fclose(fp2);

     //Return final number of steps and final state
     returnArray[0] = stepCounter;
     returnArray[1] = currentStateIndex;
}


//UNIT TESTS

//This function will test is the initialization function works correctly
void testInitialize(){
        // We want to make sure that everything in the struct is -1 after the initialization.
        // Loop over the data structure to make sure

        struct states fsmDefTest[50];

        initialize(fsmDefTest);

        for (int i = 0; i<50; i++){
                if (fsmDefTest[i].currentState != -1){
                        printf("Error. The initialization did not work!\n");
                        printf("i is: %d\n", i);
                        printf("it's value is: %d\n", fsmDefTest[i].currentState);
                        exit(0);
                }
                for (int j = 0; j<26; j++){
                        if (fsmDefTest[i].findNext[j] != -1){
                                printf("Error. The initialization did not work!\n");
                                printf("i is: %d\n", i);
                                printf("j is: %d\n", j);
                                printf("it's value is: %d\n", fsmDefTest[i].findNext[j]);
                                exit(0);
                        }
                }
        }

        printf("The initialization function worked!\n");
        return;
}

void testRegex(){
        // We want to make sure our regex pattern is correct and works correctly.
        // Input different strings to the regex pattern and check for the correct results
        // Check if it will throw an error if the middle argument is not a letter

        int value;

        //Compile regex to make sure the line of the definition file is in the correct format (integer:character>integer)

        // Check if it will capture 3 digit ints, 2 digit ints, and 1 digit ints
        value = checkRegex("123:a>435");
        if (value == REG_NOMATCH) {
                printf("This regex function was unable to capture 3 digit integers\n");
                exit(0);
        }
        value = checkRegex("12:a>35");
        if (value == REG_NOMATCH) {
                printf("This regex function was unable to capture 2 digit integers\n");
                exit(0);
        }
        value = checkRegex("2:a>5");
        if (value == REG_NOMATCH) {
                printf("This regex function was unable to capture 2 digit integers\n");
                exit(0);
        }

        // Check if it will capture uppercase and lowercase letters
        value = checkRegex("12:a>32");
        if (value == REG_NOMATCH) {
                printf("This regex function was unable to capture a lowercase input\n");
                exit(0);
        }
        value = checkRegex("12:B>32");
        if (value == REG_NOMATCH) {
                printf("This regex function was unable to capture an uppercase input\n");
                exit(0);
        }

        // Check if it will throw an error if one of the delimiters is missing
        value = checkRegex("12B>32");
        if (value != REG_NOMATCH) {
                printf("This regex function was unable to catch a missing delimiter error (:)\n");
                exit(0);
        }
        value = checkRegex("12:B32");
        if (value != REG_NOMATCH) {
                printf("This regex function was unable to catch a missing delimiter error (>)\n");
                exit(0);
        }


        // Check if it will throw an error is the first and last arguments are not integers
        value = checkRegex("@:B>32");
        if (value != REG_NOMATCH) {
                printf("This regex function was unable to catch an incorrect first integer argument\n");
                exit(0);
        }
        value = checkRegex("1:B>#");
        if (value != REG_NOMATCH) {
                printf("This regex function was unable to catch an incorrect second integer argument\n");
                exit(0);
        }

        // Check if it will throw an error if the middle argument is not a letter
        value = checkRegex("1:3>2");
        if (value != REG_NOMATCH) {
                printf("This regex function was unable to catch an incorrect character argument\n");
                exit(0);
        }

 printf("The regex function worked correctly!\n");

        return;
}




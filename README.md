# ComputerSystemsFSM


Welcome to my final computer systems project! 

To compile the program, run "make." It will save the executable as "fsm," which will take two command line arguments.

The unit  tests will run before the program begins running. 

All helper functions are included in fsmFunctions.c/fsmFunctions.h, which the makefile will compile with fsm.c

The makefile will also compile an executable called "fsmTest." This provides testing for valid output. 
All of the necessary input files are included here. To test for different outputs:

Will the program fail if there are over 250 input values?
- To test, run fsmOutputTest.c with the files fsmDef.txt and over250.txt
- "fsmOutputTest fsmDef.txt over250.txt"
 
Will the program fail if there are more than 50 states?
- To test, run fsmOutputTest.c with the files fsmDefOver50.txt and fsmInput.txt
- "fsmOutputTest fsmDefOver50.txt over250.txt"

Will the program fail if there was an incorrect (not an alphabetic character) input?
- To test, run fsmOutputTest.c with the files fsmDef.txt and fsmInputNotAlpha.txt
- "fsmOutputTest fsmDef.txt fsmInputNotAlpha.txt"

Will the program fail if no state 0 was provided?
- To test, run fsmOutTest.c with the files fsmDefNoZero.txt and fsmInput.txt
- "fsmOutputTest fsmDefNoZero.txt fsmInput.txt"

Will the program give the correct output for these input files?
- To test, run fsmOutputTest.c with the files fsmDef.txt and fsmInput.txt
- "fsmOutputTest fsmDef.txt fsmInput.txt:
- Check for this output:

FSM has 16 transitions
 at step 0, input a transitions from state 0 to state 1
 at step 1, input a transitions from state 1 to state 0
 at step 2, input a transitions from state 0 to state 1
 at step 3, input a transitions from state 1 to state 0
 at step 4, input b transitions from state 0 to state 1
 at step 5, input c transitions from state 1 to state 2
 at step 6, input b transitions from state 2 to state 1
 at step 7, input c transitions from state 1 to state 2
after 8 steps, state machine finished successfully at state 2


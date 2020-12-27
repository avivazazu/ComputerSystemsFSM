all: fsm fsmTest

fsm: fsm.c fsmFunctions.c
	gcc -o fsm fsm.c fsmFunctions.c


fsmTest: fsmOutputTest.c fsmFunctions.c
	gcc -o fsmTest fsmOutputTest.c fsmFunctions.c

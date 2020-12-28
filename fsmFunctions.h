struct states {
        int currentState;
        int findNext[26];
};

int checkRegex(char* currentLine);

void initialize(struct states fsmDef[]);

int interpretFirstFile(struct states fsmDef[], char* fileName);

void interpretSecondFile(struct states fsmDef[], char* fileName, int returnArray[]);

void testInitialize();

void testRegex();

void testStrParser();

void strParser(char line[], char **strTracker,char **currentStateInput, char **input, char **nextState);

int fillOutStructs(struct states fsmDef[], int numberOfStates, int currentStateIndex,  int index, int nextStateInt);

int getNextState(struct states fsmDef[], int stepCounter, int currentStateIndex, char line[]);



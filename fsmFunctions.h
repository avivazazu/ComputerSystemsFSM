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

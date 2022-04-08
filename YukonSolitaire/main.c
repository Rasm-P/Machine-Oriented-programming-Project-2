#include <stdio.h>
#include <stdbool.h>
#define MAX_STRING 20
#define LIMIT 10000

int LD(char lastCommand[]);

int main() {

    bool isRunning = true;
    char lastCommand[MAX_STRING] = {0};
    int result;
    char resultMessage[MAX_STRING];

    while (isRunning) {
        if (lastCommand[0] == 'L' && lastCommand[1] == 'D') {
            result = LD(lastCommand);
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'W') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'L') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'R') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'D') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'Q' && lastCommand[1] == 'Q') {
            printf("TO DO!\n");
            break; //replace
        } else if (lastCommand[0] == 'P') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'Q') {
            printf("TO DO!\n");
        } else if (lastCommand[0] != 0){
            //Game moves
            printf("TO DO!\n");
        }

        if (lastCommand[0] != 0) {
            printf("LAST command: %s\n", lastCommand);
            if (result == 0) {
                printf("Message: OK\n");
            } else {
                printf("Message: %s\n", resultMessage);
            }
        }
        printf("INPUT > :");
        scanf("%s", lastCommand);
    }
    return 0;
}

int LD(char lastCommand[]) {
    if (lastCommand[2] == '<') {
        char optionalParameter[MAX_STRING];
        int j = 0;
        for (int i = 3; i < MAX_STRING; i++) {
            if (lastCommand[i] == '>') {
                break;
            }
            optionalParameter[j] = lastCommand[i];
            j++;
        }
        optionalParameter[j] = '\0';
        printf("%s\n",optionalParameter);

        FILE * infile;
        infile = fopen(optionalParameter, "r");
        if (infile != NULL) {
            char data[LIMIT];
            int i = 0;
            while((fscanf(infile, "%s",&data[i]) != EOF) && i < LIMIT) {
                i++;
            }
            fclose(infile);
            printf("%S\n",data); //Still needs work
        } else {
            printf("Filename could not be found!\n");
            return -1;
        }
    } else {
        printf("TO DO!\n");
    }
    return 0;
}

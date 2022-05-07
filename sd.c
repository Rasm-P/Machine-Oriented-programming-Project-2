#include "header.h"
#include <stdlib.h>
#include <stdio.h>

// Saves the current card deck to a savefile with a default or user provided name
int SD(char lastCommand[], node *cardDeck, char **resultMessage) {
    FILE *outfile;

    // If the optional user parameter is given starting with a '<' bracket
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

        // File with name optionalParameter is opened in write mode
        outfile = fopen(optionalParameter, "w");
    } else {

        // File with default name is opened in write mode
        outfile = fopen("cards.txt", "w");
    }

    // If the file was opened successfully
    if (outfile != NULL) {

        // Write node content to the file for each line
        node* current = cardDeck -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c\n", current->face, current->suit);
            current = current -> next;
        }
        fflush(outfile);
        fclose(outfile);
    }
        // The file could not be opened
    else {
        *resultMessage = "Something went wrong with the save file!";
        return 0;
    }
    return 1;
}
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

// Saves the current state of a card game to a savefile with a default or user provided name
int S(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
    FILE *outfile;

    // If the optional user parameter is given starting with a '<' bracket
    if (lastCommand[1] == '<') {

        // The user parameter is copied to optionalParameter
        char optionalParameter[MAX_STRING];
        int j = 0;
        for (int i = 2; i < MAX_STRING; i++) {
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
        outfile = fopen("saveFile.txt", "w");
    }

    // If the file was opened successfully
    if (outfile != NULL) {

        // Write node content to the file for each line with columns and foundations separated by '-'
        node* current;
        current = C1 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C2 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C3 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C4 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C5 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C6 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C7 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation1 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation2 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation3 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation4 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n", current->face, current->suit, current->hidden);
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
#include "header.h"
#include <stdlib.h>
#include <stdio.h>


extern char faceStr[13];
extern char suitStr[4];

// Loads in a game state from a .txt file with a given name
int L(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
    if (lastCommand[1] == '<') {

        // Copies the characters of the given user input within < > brackets to optionalParameter
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

        // Opens a file with name optionalParameter in read mode
        FILE *infile;
        infile = fopen(optionalParameter, "r");
        if (infile != NULL) {

            // Unloads the previously held card nodes in C1 to C7 and foundation1 to 4
            unloadFullCardDeck(C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);

            node* controlCardDeck = malloc(sizeof(node));
            controlCardDeck -> next = NULL;
            insertCardDeck(controlCardDeck);

            // Reads each line of the file whilst counting the '-' indicating separation between columns and foundations
            int lineCount = 0;
            int cardCount = 0;
            char line[5];
            int i = 0;
            node* current = C1;
            while (fgets(line, sizeof(line), infile)) {
                lineCount++;
                if (line[0] == '-') {
                    i++;
                    switch (i) {
                        case 1:
                            current = C2;
                            break;
                        case 2:
                            current = C3;
                            break;
                        case 3:
                            current = C4;
                            break;
                        case 4:
                            current = C5;
                            break;
                        case 5:
                            current = C6;
                            break;
                        case 6:
                            current = C7;
                            break;
                        case 7:
                            current = foundation1;
                            break;
                        case 8:
                            current = foundation2;
                            break;
                        case 9:
                            current = foundation3;
                            break;
                        case 10:
                            current = foundation4;
                            break;
                    }
                    continue;
                } else {
                    cardCount++;
                }

                // Uses file content to create card nodes that are added to the linked list current
                current -> next = malloc(sizeof(node));
                current = current -> next;
                current -> next = NULL;
                current -> face = line[0];
                current -> suit = line[1];
                current -> hidden = line[2]-'0';

                // Uses a control card deck to look for duplicates and illegal card formats
                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> suit == current -> suit && currentControl -> face == current -> face) {
                        if (currentControl -> hidden == 1) {
                            currentControl -> hidden = 0;
                            break;
                        } else {
                            sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is a duplicate.", lineCount, current -> face, current -> suit);
                            fclose(infile);
                            unloadCards(controlCardDeck);
                            unloadFullCardDeck(C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
                            return 0;
                        }
                    }
                    currentControl = currentControl -> next;
                }
                if (currentControl -> next == NULL && currentControl -> suit != current -> suit && currentControl -> face != current -> face) {
                    sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is of illegal format.", lineCount, current -> face, current -> suit);
                    fclose(infile);
                    unloadCards(controlCardDeck);
                    unloadFullCardDeck(C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
                    return 0;
                }
            }
            fclose(infile);

            // Check if there are exactly 52 cards
            if (cardCount != 52) {
                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> hidden == 0) {
                        sprintf(*resultMessage, "Error in savefile! There are not 52 cards as card: %c%c is missing.", currentControl -> face, currentControl -> suit);
                        unloadCards(controlCardDeck);
                        unloadFullCardDeck(C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
                        return 0;
                    }
                    currentControl = currentControl -> next;
                }
            }
        } else {
            *resultMessage = "Error. File does not exist!";
            return 0;
        }
    } else {
        *resultMessage = "Error. No filename was given!";
        return 0;
    }
    return 1;
}
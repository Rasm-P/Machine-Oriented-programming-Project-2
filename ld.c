#include "header.h"
#include <stdlib.h>
#include <stdio.h>

// Loads in a deck of cards from a .txt file with a given name
int LD(char lastCommand[], node *cardDeck, char **resultMessage) {

    // If cardDeck is not empty then unload its nodes from memory
    if (cardDeck -> next != NULL) {
        unloadCards(cardDeck -> next);
        cardDeck -> next = NULL;
    }
    if (lastCommand[2] == '<') {

        // Copies the characters of the given user input within < > brackets to optionalParameter
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

        // Opens a file with name optionalParameter in read mode
        FILE *infile;
        infile = fopen(optionalParameter, "r");
        if (infile != NULL) {
            node* controlCardDeck = malloc(sizeof(node));
            controlCardDeck -> next = NULL;
            insertCardDeck(controlCardDeck);

            // Reads each line of the file
            int lineCount = 0;
            char line[4];
            node* current = cardDeck;
            while (fgets(line, sizeof(line), infile)) {
                lineCount++;

                // Uses file content to create card nodes that are added to the linked list current
                current -> next = malloc(sizeof(node));
                current = current -> next;
                current -> next = NULL;
                current -> face = line[0];
                current -> suit = line[1];
                current -> hidden = 1;

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
                            unloadCards(cardDeck -> next);
                            cardDeck -> next = NULL;
                            return 0;
                        }
                    }
                    currentControl = currentControl -> next;
                }
                if (currentControl -> next == NULL && currentControl -> suit != current -> suit && currentControl -> face != current -> face) {
                    sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is of illegal format.", lineCount, current -> face, current -> suit);
                    fclose(infile);
                    unloadCards(controlCardDeck);
                    unloadCards(cardDeck -> next);
                    cardDeck -> next = NULL;
                    return 0;
                }
            }
            fclose(infile);

            // Check if there are exactly 52 cards
            if (lineCount != 52) {
                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> hidden == 1) {
                        sprintf(*resultMessage, "Error in savefile! There are not 52 cards as card: %c%c is missing.", currentControl -> face, currentControl -> suit);
                        unloadCards(controlCardDeck);
                        if (cardDeck -> next != NULL) {
                            unloadCards(cardDeck->next);
                        }
                        cardDeck -> next = NULL;
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

        // If no name was given, a new deck of cards is created and added to cardDeck
        insertCardDeck(cardDeck);
    }
    return 1;
}
#include "header.h"
#include <stdlib.h>
#include <stdio.h>


int LD(char lastCommand[], node *cardDeck, char **resultMessage) {
    if (cardDeck -> next != NULL) {
        unloadCards(cardDeck -> next);
        cardDeck -> next = NULL;
    }
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
        FILE *infile;
        infile = fopen(optionalParameter, "r");
        if (infile != NULL) {
            node* controlCardDeck = malloc(sizeof(node));
            controlCardDeck -> next = NULL;
            insertCardDeck(controlCardDeck);

            int lineCount = 0;
            char line[4];
            node* current = cardDeck;
            while (fgets(line, sizeof(line), infile)) {
                lineCount++;

                current -> next = malloc(sizeof(node));
                current = current -> next;
                current -> next = NULL;
                current -> suit = line[0];
                current -> face = line[1];
                current -> hidden = 1;

                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> suit == current -> suit && currentControl -> face == current -> face) {
                        if (currentControl -> hidden == 1) {
                            currentControl -> hidden = 0;
                            break;
                        } else {
                            sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is a duplicate.", lineCount, current -> suit, current -> face);
                            fclose(infile);
                            unloadCards(controlCardDeck);
                            unloadCards(cardDeck -> next);
                            cardDeck -> next = NULL;
                            return -1;
                        }
                    }
                    currentControl = currentControl -> next;
                }
                if (currentControl -> next == NULL && currentControl -> suit != current -> suit && currentControl -> face != current -> face) {
                    sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is of illegal format.", lineCount, current -> suit, current -> face);
                    fclose(infile);
                    unloadCards(controlCardDeck);
                    unloadCards(cardDeck -> next);
                    cardDeck -> next = NULL;
                    return -1;
                }
            }
            fclose(infile);
            if (lineCount != 52) {
                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> hidden == 1) {
                        sprintf(*resultMessage, "Error in savefile! There are not 52 cards as card: %c%c is missing.", currentControl -> suit, currentControl -> face);
                        unloadCards(controlCardDeck);
                        if (cardDeck -> next != NULL) {
                            unloadCards(cardDeck->next);
                        }
                        cardDeck -> next = NULL;
                        return -1;
                    }
                    currentControl = currentControl -> next;
                }
            }
        } else {
            *resultMessage = "Error. File does not exist!";
            return -1;
        }
    } else {
        insertCardDeck(cardDeck);
    }
    return 0;
}
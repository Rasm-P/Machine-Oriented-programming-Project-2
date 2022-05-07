#include "header.h"
#include <stdlib.h>

// Deals a card deck into columns and unloads the previously held card nodes in C1 to C7 and foundation1 to 4
int P(int* STARTUP, node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4, char **resultMessage){

    // If card deck is not empty
    if (cardDeck -> next != NULL) {
        node* newDeck = malloc(sizeof(node));
        newDeck -> next = NULL;
        node* current = cardDeck -> next;
        while (current != NULL) {
            insertElement(&newDeck, current -> face, current -> suit, 1);
            current = current -> next;
        }

        // Sets to play phase
        *STARTUP = 0;

        // Unloads the previously held card nodes in C1 to C7 and foundation1 to 4
        unloadFullCardDeck(C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);

        // Deals a card node into the correct column using and incrementor i and modulus 7. Also keeps tract of cards as a 7x11 grid to ensure the correct number of cards is dealt
        int i = 0;
        newDeck = newDeck->next;
        node *temp;
        while (newDeck != NULL) {
            temp = newDeck;
            newDeck = newDeck->next;
            if (i == 0) {
                C1->next = temp;
                C1->next->hidden = 0;
                C1->next->next = NULL;
            } else if ((i % 7 == 1) && i <= 36) {
                C2->next = temp;
                C2 = C2->next;
                if (i>=8) {
                    C2->hidden=0;
                }
                C2->next = NULL;
            } else if ((i % 7 == 2) && i <= 44) {
                C3->next = temp;
                C3 = C3->next;
                if (i>=16) {
                    C3->hidden=0;
                }
                C3->next = NULL;
            } else if ((i % 7 == 3) && i <= 52) {
                C4->next = temp;
                C4 = C4->next;
                if (i>=24) {
                    C4->hidden=0;
                }
                C4->next = NULL;
            } else if ((i % 7 == 4) && i <= 60) {
                C5->next = temp;
                C5 = C5->next;
                if (i>=32) {
                    C5->hidden=0;
                }
                C5->next = NULL;
            } else if ((i % 7 == 5) && i <= 68) {
                C6->next = temp;
                C6 = C6->next;
                if (i>=40) {
                    C6->hidden=0;
                }
                C6->next = NULL;
            } else if ((i % 7 == 6) && i <= 76) {
                C7->next = temp;
                C7 = C7->next;
                if (i>=48) {
                    C7->hidden=0;
                }
                C7->next = NULL;
                if (i >= 6 && i < 41) {
                    i++;
                } else if (i == 41) {
                    i = i + 2;
                } else if (i == 48) {
                    i = i + 3;
                } else if (i == 55) {
                    i = i + 4;
                } else if (i == 62) {
                    i = i + 5;
                } else if (i == 69) {
                    i = i + 6;
                }
            }
            i++;
        }
        return 1;
    }
    // Card deck is empty
    else {
        *resultMessage = "Error. No deck has been loaded!";
        return 0;
    }
}
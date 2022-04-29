#include "header.h"
#include <stdlib.h>


int P(int* STARTUP, node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4, char **resultMessage){
    if (cardDeck -> next != NULL) {

        node* newDeck = malloc(sizeof(node));
        newDeck -> next = NULL;
        node* current = cardDeck -> next;
        while (current != NULL) {
            insertElement(&newDeck, current -> suit, current -> face, 1);
            current = current -> next;
        }

        *STARTUP = 0;
        unloadCards(C1->next);
        C1->next = NULL;
        unloadCards(C2->next);
        C2->next = NULL;
        unloadCards(C3->next);
        C3->next = NULL;
        unloadCards(C4->next);
        C4->next = NULL;
        unloadCards(C5->next);
        C5->next = NULL;
        unloadCards(C6->next);
        C6->next = NULL;
        unloadCards(C7->next);
        C7->next = NULL;
        unloadCards(foundation1->next);
        foundation1->next = NULL;
        unloadCards(foundation2->next);
        foundation2->next = NULL;
        unloadCards(foundation3->next);
        foundation3->next = NULL;
        unloadCards(foundation4->next);
        foundation4->next = NULL;

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
        return 0;
    } else {
        *resultMessage = "Error. No deck has been loaded!";
        return -1;
    }
}
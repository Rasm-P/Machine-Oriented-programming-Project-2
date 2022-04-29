#include "header.h"
#include <stdlib.h>


void unloadCards(node* cards) {
    if (cards != NULL) {
        node *temp;
        while (cards->next != NULL) {
            temp = cards;
            cards = cards->next;
            temp->next = NULL;
            free(temp);
            temp = NULL;
        }
        cards = NULL;
    }
}

void unloadFullCardDeck(node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4) {
    unloadCards(C1 -> next);
    C1 -> next = NULL;
    unloadCards(C2 -> next);
    C2 -> next = NULL;
    unloadCards(C3 -> next);
    C3 -> next = NULL;
    unloadCards(C4 -> next);
    C4 -> next = NULL;
    unloadCards(C5 -> next);
    C5 -> next = NULL;
    unloadCards(C6 -> next);
    C6 -> next = NULL;
    unloadCards(C7 -> next);
    C7 -> next = NULL;
    unloadCards(foundation1 -> next);
    foundation1 -> next = NULL;
    unloadCards(foundation2 -> next);
    foundation2 -> next = NULL;
    unloadCards(foundation3 -> next);
    foundation3 -> next = NULL;
    unloadCards(foundation4 -> next);
    foundation4 -> next = NULL;
}
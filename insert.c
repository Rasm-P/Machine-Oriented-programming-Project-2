#include "header.h"
#include <stdlib.h>


extern char faceStr[13];
extern char suitStr[4];

void insertElement(node** root, char face, char suit, int hidden) {

    node* newNode = malloc(sizeof(node));
    newNode -> next = NULL;
    newNode -> face = face;
    newNode -> suit = suit;
    newNode -> hidden = hidden;

    node* current = *root;
    while (current -> next != NULL) {
        current = current -> next;
    }

    current -> next = newNode;

}

void insertCardDeck(node* cardDeck) {
    int j = 0;
    for(int i = 0; i < 52; ++i) {
        if (i != 0 && i % 13 == 0) {
            j++;
        }
        insertElement(&cardDeck, faceStr[i % 13], suitStr[j], 1);
    }

}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct node {

    char suit;
    char face;
    int hidden;

    struct node* next;

}node;

void insertElement(node** root, char suit, char face, int hidden);

int main () {

    char suitStr [13] = { 'A', '2', '3', '4', '5', '6',
                          '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char faceStr [4] = {'C', 'D', 'H', 'K'};




    return 0;
}


void insertElement(node** root, char suit, char face, int hidden) {

    node* newNode = malloc(sizeof(node));
    newNode -> next = NULL;
    newNode -> suit = suit;
    newNode -> face = face;
    newNode -> hidden = hidden;

    node* current = *root;
    while (current -> next != NULL) {

        current = current -> next;
    }

    current -> next = newNode;

}

insertCardDeck(node* cardDeck) {

char suitStr[13] = {'A' ,'2', '3', '4', '5', '6', '7', '8', '9',
                    'T', 'J', 'Q', 'K'};
char faceStr[4] = {'C', 'D', 'H', 'S'};

for(int i = 0; i < 52; ++i) {

insertElement( &cardDeck, suitStr[i%13], faceStr[i%4], 0);
}

}
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
void insertCardDeck(node* cardDeck);


int main () {

    char suitStr [13] = { 'A', '2', '3', '4', '5', '6',
                          '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char faceStr [4] = {'C', 'D', 'H', 'K'};

    node* ushuffledDeck = malloc(sizeof(node));
    insertCardDeck(ushuffledDeck);

    node* C1 = malloc(sizeof(node));
    node* C2 = malloc(sizeof(node));
    node* C3 = malloc(sizeof(node));
    node* C4 = malloc(sizeof(node));
    node* C5 = malloc(sizeof(node));
    node* C6 = malloc(sizeof(node));
    node* C7 = malloc(sizeof(node));



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

void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7) {

    int k = 51;
    int i = 0;





}

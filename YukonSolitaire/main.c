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
void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7);


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

    insertBlocks(suitStr, faceStr, C1, C2, C3, C4, C5, C6, C7);

    char userInput [20] = {0};
    char exit [] = "QQ";
    char brackets [] = "LD";
    char wrongCommand [] = "Command does not exist!";
    char correctCommand [] = "OK";



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

void insertCardDeck(node* cardDeck) {

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

    while ( i < 52 ) {
        insertElement( &C1, suitStr [i % 13], faceStr [i % 4], 0);
        i++;

        if (i > k) {
            break;
        }
        insertElement( &C2, suitStr [ i % 13], faceStr [i % 4], 0);
        i++;

        if (i > k) {
            break;
        }
        insertElement(&C3, suitStr [i % 13], faceStr [i % 4], 0);
        i++;

        if (i > k) {
            break;

        }
        insertElement(&C4, suitStr [i % 13], faceStr [i % 4], 0);
        i++;

        if (i > k )  {
            break;
        }
        insertElement(&C5, suitStr [i % 13], faceStr [i % 4], 0);
        i++;

        if (i > k) {
            break;
        }
        insertElement(&C6, suitStr[i % 13], faceStr [i % 4], 0);
        i++;

        if (i > k) {
            break;
        }
        insertElement(&C7, suitStr [i % 13], faceStr [i % 4], 0);
        i++

        if (i > k) {
            break;
        }
    }


}

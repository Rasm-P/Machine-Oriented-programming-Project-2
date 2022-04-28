#define COMMAND_STRING 30
#define MAX_STRING 120
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.c"
#include "unload.c"
#include "insert.c"
#include "sd.c"
#include "sw.c"
#include "ld.c"
#include "qq.c"
#include "q.c"
#include "p.c"
#include "l.c"
#include "s.c"
#include "display.c"


int STARTUP = 1;

int SD(char lastCommand[], node *cardDeck, char **resultMessage);
int SW(node* cardDeck, char **resultMessage);
int LD(char lastCommand[], node *cardDeck, char **resultMessage);
void QQ(node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4);
void Q(int* STARTUP);
int P(int* STARTUP, node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4, char **resultMessage);
void unloadCards(node* cards);
void unloadFullCardDeck(node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4);
void insertElement(node** root, char suit, char face, int hidden);
void insertCardDeck(node* cardDeck);
void displayDeck(node* cardDeck, node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, int STARTUP);
int L(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage);
int S(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage);
void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7);
void shuffleCardsRandom(node* source, node* dist);

int main() {
    node* cardDeck = malloc(sizeof(node));
    cardDeck -> next = NULL;

    node* C1 = malloc(sizeof(node));
    C1 -> next = NULL;
    node* C2 = malloc(sizeof(node));
    C2 -> next = NULL;
    node* C3 = malloc(sizeof(node));
    C3 -> next = NULL;
    node* C4 = malloc(sizeof(node));
    C4 -> next = NULL;
    node* C5 = malloc(sizeof(node));
    C5 -> next = NULL;
    node* C6 = malloc(sizeof(node));
    C6 -> next = NULL;
    node* C7 = malloc(sizeof(node));
    C7 -> next = NULL;

    node* foundation1 = malloc(sizeof(node));
    foundation1 -> next = NULL;
    node* foundation2 = malloc(sizeof(node));
    foundation2 -> next = NULL;
    node* foundation3 = malloc(sizeof(node));
    foundation3 -> next = NULL;
    node* foundation4 = malloc(sizeof(node));
    foundation4 -> next = NULL;

    bool isRunning = true;
    char lastCommand[COMMAND_STRING] = {0};
    int result = 0;
    char *resultMessage = (char*) malloc(sizeof(char) * MAX_STRING);

    while (isRunning) {
        if (STARTUP) {
            if (lastCommand[0] == 'L' && lastCommand[1] == 'D') {
                result = LD(lastCommand, cardDeck, &resultMessage);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'W') {
                result = SW(cardDeck, &resultMessage);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'L') {
                printf("TO DO!\n");
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'R') {
                printf("TO DO!\n");
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'D') {
                result = SD(lastCommand, cardDeck, &resultMessage);
            }  else if (lastCommand[0] == 'P') {
                result = P(&STARTUP, cardDeck, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4, &resultMessage);
            }  else {
                result = 1;
                resultMessage = "The chosen command does not exist in the STARTUP phase!";
            }
        } else {
            if (lastCommand[0] == 'Q') {
                Q(&STARTUP);
            }
            else if (lastCommand[0] == 'L' ) {
                result = L(lastCommand, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4,
                            &resultMessage);
            }
            else if (lastCommand[0] == 'S') {
                result = S(lastCommand, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4,
                            &resultMessage);
            } else {
                //Game moves
                printf("TO DO!\n");
            }
        }
        if (lastCommand[0] == 'Q' && lastCommand[1] == 'Q') {
            printf("Thank you for playing!\n");
            QQ(cardDeck, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
            break;
        }

        if (lastCommand[0] != 0) {
            printf("LAST command: %s\n", lastCommand);
            if (result == 0) {
                printf("Message: OK\n");
            } else {
                printf("Message: %s\n", resultMessage);
            }
        }
        if (lastCommand[0] != 'S' && lastCommand[1] != 'W') {
            displayDeck(cardDeck, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4,
                        STARTUP);
        }
        printf("INPUT > :");
        scanf("%s", lastCommand);
    }
}

void shuffleCardsRandom(node* source, node* dist) {

    char suit[52];
    char face[52];
    char hidden[52];

    node* current = source;
    current = current -> next;

    int counter = 0;

    while (current != NULL) {
        suit[counter] = current -> suit;
        face[counter] = current -> face;
        hidden[counter] = current -> hidden;

        counter++;
        current = current -> next;
    }

    for (int i = 0; i < 52; ++i) {
        insertElement( &dist, suit[i], face[i], hidden[i]);
    }


}

#include "header.h"
#include <stdlib.h>
#include <stdio.h>


char faceStr[13] = {'A', '2', '3', '4', '5', '6',
                    '7', '8', '9', 'T', 'J', 'Q', 'K'};
char suitStr[4] = {'C', 'D', 'H', 'S'};
int STARTUP = 1;

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
    foundation1 -> suit = suitStr[0];
    node* foundation2 = malloc(sizeof(node));
    foundation2 -> next = NULL;
    foundation2 -> suit = suitStr[1];
    node* foundation3 = malloc(sizeof(node));
    foundation3 -> next = NULL;
    foundation3 -> suit = suitStr[2];
    node* foundation4 = malloc(sizeof(node));
    foundation4 -> next = NULL;
    foundation4 -> suit = suitStr[3];

    int isRunning = 1;
    char lastCommand[COMMAND_STRING] = {0};
    int result = 1;
    char *resultMessage = (char*) malloc(sizeof(char) * MAX_STRING);

    while (isRunning) {
        if (STARTUP) {
            if (lastCommand[0] == 'L' && lastCommand[1] == 'D') {
                result = LD(lastCommand, cardDeck, &resultMessage);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'W') {
                result = SW(cardDeck, &resultMessage);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'I') {
                result = SI(lastCommand, cardDeck, &resultMessage);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'R') {
                SR(cardDeck);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'D') {
                result = SD(lastCommand, cardDeck, &resultMessage);
            }  else if (lastCommand[0] == 'P') {
                result = P(&STARTUP, cardDeck, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4, &resultMessage);
            }  else {
                result = 0;
                resultMessage = "The chosen command does not exist in the STARTUP phase!";
            }
        } else {
            if (lastCommand[0] == 'Q') {
                Q(&STARTUP);
            }
            else if (lastCommand[0] == 'L') {
                result = L(lastCommand, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4,
                            &resultMessage);
            }
            else if (lastCommand[0] == 'S') {
                result = S(lastCommand, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4,
                            &resultMessage);
            } else {
                result = GameMoves(lastCommand, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4,
                                   &resultMessage);
            }
            if (isGameWon(C1, C2, C3, C4, C5, C6, C7)) {
                printf("You have won the game!");
                QQ(cardDeck, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
            }
        }
        if (lastCommand[0] == 'Q' && lastCommand[1] == 'Q') {
            printf("Thank you for playing!\n");
            QQ(cardDeck, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
            break;
        }

        if (!STARTUP || (lastCommand[0] != 'S' || lastCommand[1] != 'W')) {
            displayDeck(cardDeck, C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4,
                        STARTUP);
        }
        if (lastCommand[0] != 0) {
            printf("LAST command: %s\n", lastCommand);
            if (result) {
                printf("Message: OK\n");
            } else {
                printf("Message: %s\n", resultMessage);
                result = 1;
            }
        }
        printf("INPUT > :");
        scanf("%s", lastCommand);
    }
}

int isGameWon(node* C1,node* C2,node* C3,node* C4,node* C5,node* C6,node* C7) {
    if (C1 -> next == NULL && C2 -> next == NULL && C3 -> next == NULL && C4 -> next == NULL && C5 -> next == NULL && C6 -> next == NULL && C7 -> next == NULL) {
        return 1;
    } else {
        return 0;
    }
}
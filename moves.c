#include "header.h"
#include <stdlib.h>
#include <string.h>


int GameMoves(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
    char fromCommand[6];
    char toCommand[3];

    int fromCommandCount = 0;
    int toCommandCount = 0;
    int isFrom = 0;
    for (int i = 0; i < strlen(lastCommand); i++) {
        if (lastCommand[i] == '-' && isFrom == 0) {
            isFrom = 1;
            i += 2;
        }
        switch (isFrom) {
            case 0:
                fromCommand[fromCommandCount] = lastCommand[i];
                fromCommandCount++;
                break;
            case 1:
                toCommand[toCommandCount] = lastCommand[i];
                toCommandCount++;
                break;
        }
    }
    fromCommand[5] = '\0';
    toCommand[2] = '\0';

    node* fromNode;
    node* fromPrevious;
    findCard(&fromNode,&fromPrevious,fromCommand,C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
    node* toNode;
    node* toPrevious;
    findCard(&toNode,&toPrevious,toCommand,C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
    if (fromNode != NULL && toNode != NULL) {
        if (!validateMove(toCommand, fromNode, toNode, resultMessage)) {
            memset(fromCommand, 0, sizeof fromCommand);
            memset(toCommand, 0, sizeof toCommand);
            return 0;
        }
        if (fromPrevious != NULL) {
            fromPrevious -> next = NULL;
            if (fromPrevious -> hidden == 1) {
                fromPrevious -> hidden = 0;
            }
        }
        toNode -> next = fromNode;
        memset(fromCommand, 0, sizeof fromCommand);
        memset(toCommand, 0, sizeof toCommand);
        return 1;
    } else {
        *resultMessage = "Error. One of the given cards or columns are not valid or might be empty!";
        memset(fromCommand, 0, sizeof fromCommand);
        memset(toCommand, 0, sizeof toCommand);
        return 0;
    }
}

void findCard(node** cardPtr, node** previousPtr, char command[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4) {
    node* previous = NULL;
    node* current = NULL;
    int column = ((int)command[1])-'0';
    if (command[0] == 'F') {
        switch(column) {
            case 1:
                current = foundation1;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 2:
                current = foundation2;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 3:
                current = foundation3;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 4:
                current = foundation4;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
        }
    } else if (command[2] == ':') {
        switch(column) {
            case 1:
                current = C1;
                while (current -> next != NULL) {
                    if (current -> face == command[3] && current -> suit == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 2:
                current = C2;
                while (current -> next != NULL) {
                    if (current -> face == command[3] && current -> suit == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 3:
                current = C3;
                while (current -> next != NULL) {
                    if (current -> face == command[3] && current -> suit == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 4:
                current = C4;
                while (current -> next != NULL) {
                    if (current -> face == command[3] && current -> suit == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 5:
                current = C5;
                while (current -> next != NULL) {
                    if (current -> face == command[3] && current -> suit == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 6:
                current = C6;
                while (current -> next != NULL) {
                    if (current -> face == command[3] && current -> suit == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 7:
                current = C7;
                while (current -> next != NULL) {
                    if (current -> face == command[3] && current -> suit == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
        }
        if (current -> next == NULL && (current -> face != command[3] || current -> suit != command[4])) {
            previous = NULL;
            current = NULL;
        }
    } else {
        switch(column) {
            case 1:
                current = C1;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 2:
                current = C2;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 3:
                current = C3;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 4:
                current = C4;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 5:
                current = C5;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 6:
                current = C6;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
            case 7:
                current = C7;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                break;
        }
    }
    *cardPtr = current;
    *previousPtr = previous;
}

int validateMove(char toCommand[], node* fromNode, node* toNode, char** resultMessage) {
    if ((getValue(fromNode)+1 != getValue(toNode)) && toCommand[0] != 'F') {
        *resultMessage = "Error. You can only move a card to a column if the card on the bottom of that column is 1 higher than the card you want to move!";
        return 0;
    } else if ((fromNode -> suit == toNode -> suit) && toCommand[0] != 'F') {
        *resultMessage = "Error. You cannot move a card to a column if the card on the bottom of that column is of the same suit!";
        return 0;
    } else if (fromNode -> next != NULL && toCommand[0] == 'F') {
        *resultMessage = "Error. If you want to put a card on a foundation, then that card should come from the bottom of a column!";
        return 0;
    } else if ((getValue(toNode)+1 != getValue(fromNode)) && getValue(toNode) != 0 && toCommand[0] == 'F') {
        *resultMessage = "Error. A card can only be placed on a foundation if the existing card on top of the foundation is 1 smaller than the card you want to place!";
        return 0;
    } else if ((fromNode -> suit != toNode -> suit && toCommand[0]) == 'F') {
        *resultMessage = "Error. A card can only be placed on a foundation if the existing card on top of the foundation if it is of the same suit";
        return 0;
    }
    return 1;
}

int getValue(node* card) {
    int value = 0;
    switch (card -> face) {
        case 'A':
            value = 1;
            break;
        case '2':
            value = 2;
            break;
        case '3':
            value = 3;
            break;
        case '4':
            value = 4;
            break;
        case '5':
            value = 5;
            break;
        case '6':
            value = 6;
            break;
        case '7':
            value = 7;
            break;
        case '8':
            value = 8;
            break;
        case '9':
            value = 9;
            break;
        case 'T':
            value = 10;
            break;
        case 'J':
            value = 11;
            break;
        case 'Q':
            value = 12;
            break;
        case 'K':
            value = 13;
            break;
    }
    return value;
}
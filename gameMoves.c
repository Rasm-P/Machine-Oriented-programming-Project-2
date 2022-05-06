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
        if (fromPrevious != NULL) {
            fromPrevious -> next = NULL;
        }
        toNode -> next = fromNode;
        return 0;
    } else {
        *resultMessage = "Error. Could not find the cards given in the command!";
        return -1;
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
                    if (current -> suit == command[3] && current -> face == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 2:
                current = C2;
                while (current -> next != NULL) {
                    if (current -> suit == command[3] && current -> face == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 3:
                current = C3;
                while (current -> next != NULL) {
                    if (current -> suit == command[3] && current -> face == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 4:
                current = C4;
                while (current -> next != NULL) {
                    if (current -> suit == command[3] && current -> face == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 5:
                current = C5;
                while (current -> next != NULL) {
                    if (current -> suit == command[3] && current -> face == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 6:
                current = C6;
                while (current -> next != NULL) {
                    if (current -> suit == command[3] && current -> face == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 7:
                current = C7;
                while (current -> next != NULL) {
                    if (current -> suit == command[3] && current -> face == command[4]) {
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
        }
        if (current -> next == NULL && (current -> suit != command[3] || current -> face != command[4])) {
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
                current = C6;
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
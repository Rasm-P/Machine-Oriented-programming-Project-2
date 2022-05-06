#include "header.h"
#include <stdlib.h>
#include <stdio.h>


int GameMoves(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
    char fromCommand[5];
    char toCommand[5];

    int fromCommandCount = 0;
    int toCommandCount = 0;
    int isFrom = 0;
    for (int i = 1; i < 15; i++) {
        if (lastCommand[i] == '>' && isFrom == 0) {
            isFrom = 1;
            i += 3;
        }
        if (lastCommand[i] != '<' && lastCommand[i] != '>') {
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
    }

    node* fromNode = NULL;
    int column = ((int)fromCommand[1])-'0';
    if (fromCommand[0] == 'F') {
        switch(column) {
            node* previous;
            node* current;
            case 1:
                current = foundation1 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 2:
                current = foundation2 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 3:
                current = foundation3 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 4:
                current = foundation4 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
        }
    } else if (fromCommand[2] == ':') {
        switch(column) {
            node* previous;
            node* current;
            case 1:
                current = C1 -> next;
                while (current -> next != NULL) {
                    if (current -> suit == fromCommand[3] && current -> face == fromCommand[4]) {
                        fromNode = current;
                        previous -> next = NULL;
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 2:
                current = C2 -> next;
                while (current -> next != NULL) {
                    if (current -> suit == fromCommand[3] && current -> face == fromCommand[4]) {
                        fromNode = current;
                        previous -> next = NULL;
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 3:
                current = C3 -> next;
                while (current -> next != NULL) {
                    if (current -> suit == fromCommand[3] && current -> face == fromCommand[4]) {
                        fromNode = current;
                        previous -> next = NULL;
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 4:
                current = C4 -> next;
                while (current -> next != NULL) {
                    if (current -> suit == fromCommand[3] && current -> face == fromCommand[4]) {
                        fromNode = current;
                        previous -> next = NULL;
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 5:
                current = C5 -> next;
                while (current -> next != NULL) {
                    if (current -> suit == fromCommand[3] && current -> face == fromCommand[4]) {
                        fromNode = current;
                        previous -> next = NULL;
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 6:
                current = C6 -> next;
                while (current -> next != NULL) {
                    if (current -> suit == fromCommand[3] && current -> face == fromCommand[4]) {
                        fromNode = current;
                        previous -> next = NULL;
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
            case 7:
                current = C7 -> next;
                while (current -> next != NULL) {
                    if (current -> suit == fromCommand[3] && current -> face == fromCommand[4]) {
                        fromNode = current;
                        previous -> next = NULL;
                        break;
                    }
                    previous = current;
                    current = current -> next;
                }
                break;
        }
    } else {
        switch(column) {
            node* previous;
            node* current;
            case 1:
                current = C1 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 2:
                current = C2 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 3:
                current = C3 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 4:
                current = C4 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 5:
                current = C5 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 6:
                current = C6 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
            case 7:
                current = C7 -> next;
                while (current -> next != NULL) {
                    previous = current;
                    current = current -> next;
                }
                previous -> next = NULL;
                break;
        }
    }

    if (fromNode == NULL) {
        *resultMessage = "Error. Something was wrong the the input command!";
        return -1;
    }
}

int findCard(node* cardPtr, node* previousPtr) {
    
}
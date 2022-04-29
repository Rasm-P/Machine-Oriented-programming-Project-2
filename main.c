#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

char suitStr[13] = { 'A', '2', '3', '4', '5', '6',
                      '7', '8', '9', 'T', 'J', 'Q', 'K'};
char faceStr[4] = {'C', 'D', 'H', 'S'};
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
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'I') {
                result = splitDeck(lastCommand, cardDeck, &resultMessage);
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
            }else {
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

    node* newPile = malloc(sizeof(node));

    int i = 1;
    //node*
    node* current = source -> next;
    while(current != NULL) {
        if (i == 1) {
            newPile -> next = current;
        }
        current = current -> next;

    }


    char suit[52];
    char face[52];
    char hidden[52];

    //node* current = source;
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

    print_list(dist);


}

int splitDeck(char lastCommand[], node* source, char **resultMessage) {
    int midValue;
    if (lastCommand[2] == '<') {
        char optionalParameter[MAX_STRING];
        int j = 0;
        for (int i = 3; i < MAX_STRING; i++) {
            if (lastCommand[i] == '>') {
                break;
            }
            optionalParameter[j] = lastCommand[i];
            j++;
        }
        optionalParameter[j] = '\0';
        midValue = atoi(optionalParameter);
    } else {
        srand(time(NULL));
        midValue = rand() % 51;
    }

    if (midValue < 52) {
        node* thirdPile = malloc(sizeof(node));
        node* firstNode = malloc(sizeof(node));
        node* secondNode = malloc(sizeof(node));

        int i = 0;
        node* current = source -> next;
        firstNode -> next = current;
        while (current != NULL && i <= midValue) {
            current = current -> next;
            i++;
        }
        node* temp = current;
        secondNode -> next = current ->next;
        temp ->next = NULL;

        firstNode = firstNode->next;
        secondNode = secondNode->next;

        node* pileCurrent = thirdPile;
        while (firstNode != NULL && secondNode != NULL) {
            pileCurrent->next = firstNode;
            firstNode = firstNode->next;
            pileCurrent = pileCurrent -> next;
            pileCurrent -> next = NULL;

            pileCurrent->next = secondNode;
            secondNode = secondNode->next;
            pileCurrent = pileCurrent -> next;
            pileCurrent -> next = NULL;
        }
        if (firstNode != NULL) {
            while (firstNode != NULL) {
                pileCurrent->next = firstNode;
                firstNode = firstNode->next;
                pileCurrent = pileCurrent -> next;
                pileCurrent -> next = NULL;
            }
        } else if (secondNode != NULL) {
            while (secondNode != NULL) {
                pileCurrent->next = secondNode;
                secondNode = secondNode->next;
                pileCurrent = pileCurrent -> next;
                pileCurrent -> next = NULL;
            }
        }
        free(thirdPile);
        free(firstNode);
        free(secondNode);
        return 0;
    } else {
        *resultMessage = "Error! You cannot choose a number larger than 52.";
        return 1;
    }
}

void print_list(node* head) {
    node* current = head;
    int count = 0;
    while (current != NULL) {
        printf("%c%c%c\n", current -> suit, current -> face, current -> hidden);
        current = current -> next;
        count ++;
    }
}

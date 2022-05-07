#include "header.h"
#include <stdlib.h>
#include <time.h>


int SI(char lastCommand[], node* source, char **resultMessage) {
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
        midValue = (rand() % 51)+1;
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
        return 1;
    } else {
        *resultMessage = "Error! You cannot choose a number larger than or equal to 52.";
        return 0;
    }
}
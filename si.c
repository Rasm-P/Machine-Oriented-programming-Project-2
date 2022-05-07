#include "header.h"
#include <stdlib.h>
#include <time.h>

// Splits a card deck and added the cards together in an alternating manner
int SI(char lastCommand[], node* source, char **resultMessage) {
    int midValue;

    // If user input is given starting with a '<' bracket. Input is converted and stored in midValue
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
    }
    // No user input was given. A random value between 1 and 52 is chosen
    else {
        srand(time(NULL));
        midValue = (rand() % 51)+1;
    }

    // midValue is less than 52
    if (midValue < 52) {
        // Three piles are created
        node* thirdPile = malloc(sizeof(node));
        node* firstNode = malloc(sizeof(node));
        node* secondNode = malloc(sizeof(node));

        // Card nodes from cardDeck is added to the fist pile until outer i is greater than midValue. Rest of cards goes to the second pile
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

        // First and second pile are put together in an alternating manner into the third pile. The rest of the remaining pile will be put on top of the third pile
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
    }
    // midValue was somehow greater than or equal to 52
    else {
        *resultMessage = "Error! You cannot choose a number larger than or equal to 52.";
        return 0;
    }
}
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

// Prints the card nodes in cardDeck to the console
int SW(node* cardDeck, char **resultMessage) {

    // If cardDeck is not empty
    if (cardDeck -> next != NULL) {

        // Prints out column names
        printf("\n\n");
        printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
        int num = 1;
        int i = 1;

        // Print out card node with a newline for every 7th node and a foundation for every 14th node
        cardDeck = cardDeck -> next;
        while (cardDeck != NULL) {

            // Prints card node face and suit
            printf("%c%c\t", cardDeck -> face, cardDeck -> suit);
            if ((i - 7) % 14 == 0) {

                printf("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
                num++;
            }
            if (i % 7 == 0 && i != 0) {
                printf("\n");
            }
            i++;
            cardDeck = cardDeck -> next;
        }
        printf("\n\n");
        return 1;
    }
    // cardDeck was empty
    else {
        *resultMessage = "Error! No deck of cards are loaded.";
        return 0;
    }
}
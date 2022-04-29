#include <stdlib.h>
#include <stdio.h>
#include "header.h"


int SW(node* cardDeck, char **resultMessage) {
    if (cardDeck -> next != NULL) {
        printf("\n\n");
        printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
        int num = 1;
        int i = 1;
        cardDeck = cardDeck -> next;
        while (cardDeck != NULL) {
            printf("%c%c\t",cardDeck -> suit, cardDeck -> face);
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
        return 0;
    } else {
        *resultMessage = "Error! No deck of cards are loaded.";
        return -1;
    }
}
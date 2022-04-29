#include "header.h"
#include <stdlib.h>
#include <time.h>


void SR(node* source) {
    node* newPile = malloc(sizeof(node));
    int i = 1;
    int random;
    node* current = source;
    while(current != NULL) {
        current = source -> next;
        source -> next = current -> next;
        current -> next = NULL;
        if (i == 1) {
            newPile -> next = current;
        } else {
            node* temp = newPile;
            int j = 1;
            srand(time(NULL));
            random = (rand() % i)+1;
            while(j < random) {
                temp = temp -> next;
                j++;
            }
            if (temp -> next == NULL) {
                temp -> next = current;
            } else {
                node* newPileTemp = temp;
                temp = temp -> next;
                newPileTemp ->next = current;
                newPileTemp ->next ->next = temp;
            }
        }
        current = source -> next;
        i++;
    }
    source -> next = newPile -> next;
    free(newPile);
}
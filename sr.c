#include "header.h"
#include <stdlib.h>
#include <time.h>

// Shuffles a card deck in a random manner
void SR(node* source) {

    node* newPile = malloc(sizeof(node));
    int i = 1;
    int random;
    node* current = source;

    // While source is not empty, the current node will be put into a new deck at a random position
    while(current != NULL) {
        current = source -> next;
        source -> next = current -> next;
        current -> next = NULL;

        // In case of the first node, there is only one position
        if (i == 1) {
            newPile -> next = current;
        }
        // Chooses a random position between 1 and the count i value
        else {
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

    // Sets the source header node next to newPile header node next
    source -> next = newPile -> next;
    free(newPile);
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct node {

    char suit;
    char face;
    int hidden;

    struct node* next;

}node;

int main () {

    char suitStr [13] = { 'A', '2', '3', '4', '5', '6',
                          '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char faceStr [4] = {'C', 'D', 'H', 'K'};


    return 0;
}
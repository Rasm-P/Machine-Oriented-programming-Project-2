#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_STRING 30

typedef struct node {
    char suit;
    char face;
    int hidden;
    struct node* next;
}node;

char suitStr [13] = { 'A', '2', '3', '4', '5', '6',
                      '7', '8', '9', 'T', 'J', 'Q', 'K'};
char faceStr [4] = {'C', 'D', 'H', 'S'};

int LD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage);
int SD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) ;
void insertElement(node** root, char suit, char face, int hidden);
void insertCardDeck(node* cardDeck);
void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7);
void displayCardDeck(node* cardDeck);
void print_list(node* head);
void displayEmptyBrackets();

int main() {
    char suitStr[13] = {'A' ,'2', '3', '4', '5', '6', '7', '8', '9',
                        'T', 'J', 'Q', 'K'};
    char faceStr[4] = {'C', 'D', 'H', 'S'};

    node* unshuffledDeck = malloc(sizeof(node));
    insertCardDeck(unshuffledDeck);

    node* C1 = malloc(sizeof(node));
    node* C2 = malloc(sizeof(node));
    node* C3 = malloc(sizeof(node));
    node* C4 = malloc(sizeof(node));
    node* C5 = malloc(sizeof(node));
    node* C6 = malloc(sizeof(node));
    node* C7 = malloc(sizeof(node));

    insertBlocks(suitStr, faceStr, C1, C2, C3, C4, C5, C6, C7);

    char userInput[20] = {0};
    char exit[] = "QQ";
    char brackets[] = "LD";
    char wrongCommand[] = "Your command does not exist!";
    char correctCommand[] = "OK";

    int hasNext = 0;
    while (hasNext == 0) {
        char message[30];

    }
    return 0;
}

int LD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
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
        FILE *infile;
        infile = fopen(optionalParameter, "r");
        if (infile != NULL) {
            char line[5];
            int i = 0;
            node* current1 = C1;
            while (fgets(line, sizeof(line), infile)) {
                if (line[0] == '-') {
                    i++;
                    switch (i) {
                        case 1:
                            current1 = C2;
                            break;
                        case 2:
                            current1 = C3;
                            break;
                        case 3:
                            current1 = C4;
                            break;
                        case 4:
                            current1 = C5;
                            break;
                        case 5:
                            current1 = C6;
                            break;
                        case 6:
                            current1 = C7;
                            break;
                        case 7:
                            current1 = foundation1;
                            break;
                        case 8:
                            current1 = foundation2;
                            break;
                        case 9:
                            current1 = foundation3;
                            break;
                        case 10:
                            current1 = foundation4;
                            break;
                    }
                    continue;
                }
                current1 -> next = malloc(sizeof(node));
                current1 = current1 -> next;
                current1 -> next = NULL;
                current1 -> suit = line[0];
                current1 -> face = line[1];
                current1 -> hidden = line[2]-'0';
            }
            fclose(infile);
        } else {
            *resultMessage = "Error. File does not exist!";
            return -1;
        }
    } else {
        insertBlocks(suitStr, faceStr, C1, C2, C3, C4, C5, C6, C7);
    }
    return 0;
}

int SD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
    FILE *outfile;
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
        outfile = fopen(optionalParameter, "w");
    } else {
        outfile = fopen("cards.txt", "w");
    }
    if (outfile != NULL) {
        node* current;
        current = C1 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C2 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C3 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C4 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C5 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C6 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C7 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation1 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation2 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation3 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation4 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fflush(outfile);
        fclose(outfile);
    } else {
        *resultMessage = "Something went wrong with the save file!";
        return -1;
    }
    return 0;
}

void insertElement(node** root, char suit, char face, int hidden) {

    node* newNode = malloc(sizeof(node));
    newNode -> next = NULL;
    newNode -> suit = suit;
    newNode -> face = face;
    newNode -> hidden = hidden;

    node* current = *root;
    while (current -> next != NULL) {
        current = current -> next;
    }

    current -> next = newNode;

}

void insertCardDeck(node* cardDeck) {
    int j = 0;
    for(int i = 0; i < 52; ++i) {
        if (i != 0 && i % 13 == 0) {
            j++;
        }
        insertElement( &cardDeck, suitStr[i%13], faceStr[j], 0);
    }

}

void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7) {

    int k = 51;
    int i = 0;
    int j = 0;

    while ( i < 52 ) {
        insertElement( &C1, suitStr [i % 13], faceStr [j], 0);
        i++;

        if (i > k) {
            break;
        } else if (i % 13 == 0) {
            j++;
        }
        insertElement( &C2, suitStr [ i % 13], faceStr [j], 0);
        i++;

        if (i > k) {
            break;
        } else if (i % 13 == 0) {
            j++;
        }
        insertElement(&C3, suitStr [i % 13], faceStr [j], 0);
        i++;

        if (i > k) {
            break;

        } else if (i % 13 == 0) {
            j++;
        }
        insertElement(&C4, suitStr [i % 13], faceStr [j], 0);
        i++;

        if (i > k )  {
            break;
        } else if (i % 13 == 0) {
            j++;
        }
        insertElement(&C5, suitStr [i % 13], faceStr [j], 0);
        i++;

        if (i > k) {
            break;
        } else if (i % 13 == 0) {
            j++;
        }
        insertElement(&C6, suitStr[i % 13], faceStr [j], 0);
        i++;

        if (i > k) {
            break;
        } else if (i % 13 == 0) {
            j++;
        }
        insertElement(&C7, suitStr [i % 13], faceStr [j], 0);
        i++;

        if (i > k) {
            break;
        } else if (i % 13 == 0) {
            j++;
        }
    }
}

void displayCardDeck(node* cardDeck) {

    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");

    if (cardDeck == NULL) {
        return;
    }

    int counter = 1;
    int num = 0;
    node* current = cardDeck;
    current = current ->next;
    while (current != NULL) {
            printf("%c%c\t", current -> suit, current ->face);
            if ((counter-7) % 14 == 0) {

                printf("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
                num++;

            }
            if (counter % 7 == 0 && counter != 0) {
                printf("\n");
            }
            current = current ->next;
            counter++;
        }
    printf("\n");
    }



    void print_list(node* head) {
    node* current = head;
    int count = 0;

    while (current != NULL) {
        printf("%c%c%c\n", current -> suit, current -> face, current -> hidden);
        current = current -> next;
        count++;
    }
}

void displayEmptyBrackets(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");

    int num = 1;
    for (int i = 1; i < 53; i++) {

        printf ("%c%c\t", '[', ']');
        if ((i-7) % 14 == 0) {

            printf ("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
            num++;
        }

        if(i % 7 == 0 && i != 0) {
            printf("\n");
        }
    }
}

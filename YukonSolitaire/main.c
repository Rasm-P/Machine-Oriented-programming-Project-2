#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_STRING 30
#define LIMIT 10000

typedef struct node {
    char suit;
    char face;
    int hidden;
    struct node* next;
}node;

char suitStr [13] = { 'A', '2', '3', '4', '5', '6',
                      '7', '8', '9', 'T', 'J', 'Q', 'K'};
char faceStr [4] = {'C', 'D', 'H', 'S'};

int LD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4);
int SD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4) ;
void insertElement(node** root, char suit, char face, int hidden);
void insertCardDeck(node* cardDeck);
void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7);

int main() {
    node* ushuffledDeck = malloc(sizeof(node));
    ushuffledDeck -> next = NULL;
    insertCardDeck(ushuffledDeck);

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
    char lastCommand[MAX_STRING] = {0};
    int result;
    char resultMessage[MAX_STRING];

    while (isRunning) {
        if (lastCommand[0] == 'L' && lastCommand[1] == 'D') {
            result = LD(lastCommand, C1,C2,C3,C4,C5,C6,C7,foundation1,foundation2,foundation3,foundation4);
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'W') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'L') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'R') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'S' && lastCommand[1] == 'D') {
            result = SD(lastCommand, C1,C2,C3,C4,C5,C6,C7,foundation1,foundation2,foundation3,foundation4);
        } else if (lastCommand[0] == 'Q' && lastCommand[1] == 'Q') {
            printf("TO DO!\n");
            break; //replace
        } else if (lastCommand[0] == 'P') {
            printf("TO DO!\n");
        } else if (lastCommand[0] == 'Q') {
            printf("TO DO!\n");
        } else if (lastCommand[0] != 0){
            //Game moves
            printf("TO DO!\n");
        }

        if (lastCommand[0] != 0) {
            printf("LAST command: %s\n", lastCommand);
            if (result == 0) {
                printf("Message: OK\n");
            } else {
                printf("Message: %s\n", resultMessage);
            }
        }
        printf("INPUT > :");
        scanf("%s", lastCommand);
    }
    return 0;
}

int LD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4) {
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
            char data[LIMIT];
            int i = 0;
            while((fscanf(infile, "%s",&data[i]) != EOF) && i < LIMIT) {
                i++;
            }
            fclose(infile);
            printf("%S\n",data); //Still needs work
        } else {
            printf("Filename could not be found!\n");
            return -1;
        }
    } else {
        insertBlocks(suitStr, faceStr, C1, C2, C3, C4, C5, C6, C7);
    }
    return 0;
}

int SD(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4) {
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
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C2 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C3 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C4 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C5 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C6 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = C7 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation1 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation2 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation3 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fprintf(outfile,"-\n");
        current = foundation4 -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c%d.\n",current->suit,current->face,current->hidden);
            current = current -> next;
        }
        fflush(outfile);
    } else {
        printf("Something went wrong with the save file!\n");
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

    char suitStr[13] = {'A' ,'2', '3', '4', '5', '6', '7', '8', '9',
                        'T', 'J', 'Q', 'K'};
    char faceStr[4] = {'C', 'D', 'H', 'S'};

    for(int i = 0; i < 52; ++i) {

        insertElement( &cardDeck, suitStr[i%13], faceStr[i%4], 0);
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

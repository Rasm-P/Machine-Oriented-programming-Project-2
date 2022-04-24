#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define COMMAND_STRING 30
#define MAX_STRING 120

typedef struct node {
    char suit;
    char face;
    int hidden;
    struct node* next;
}node;

char suitStr [13] = { 'A', '2', '3', '4', '5', '6',
                      '7', '8', '9', 'T', 'J', 'Q', 'K'};
char faceStr [4] = {'C', 'D', 'H', 'S'};
int STARTUP = 1;

int LD(char lastCommand[], node *cardDeck, char **resultMessage);
int SD(char lastCommand[], node *cardDeck, char **resultMessage);
int SW(node* cardDeck, char **resultMessage);
void QQ(node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4);
void Q(int* STARTUP);
int P(int* STARTUP, node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4, char **resultMessage);
void unloadCards(node* cards);
void insertElement(node** root, char suit, char face, int hidden);
void insertCardDeck(node* cardDeck);
void displayEmptyBrackets(node* cardDeck);
int L(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage);
int S(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage);
void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7);
void shuffleCardsRandom(node* source, node* dist);

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
    int result;
    char *resultMessage = (char*) malloc(sizeof(char) * MAX_STRING);

    while (isRunning) {
        if (STARTUP) {
            if (lastCommand[0] == 'L' && lastCommand[1] == 'D') {
                result = LD(lastCommand, cardDeck, &resultMessage);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'W') {
                result = SW(cardDeck, &resultMessage);
            } else if (lastCommand[0] == 'S' && lastCommand[1] == 'L') {
                printf("TO DO!\n");
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
            } else {
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
        displayEmptyBrackets(cardDeck);
        printf("INPUT > :");
        scanf("%s", lastCommand);
    }
    return 0;
}

int LD(char lastCommand[], node *cardDeck, char **resultMessage) {
    if (cardDeck -> next != NULL) {
        unloadCards(cardDeck -> next);
        cardDeck -> next = NULL;
    }
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
            node* controlCardDeck = malloc(sizeof(node));
            controlCardDeck -> next = NULL;
            insertCardDeck(controlCardDeck);

            int lineCount = 0;
            char line[4];
            node* current = cardDeck;
            while (fgets(line, sizeof(line), infile)) {
                lineCount++;

                current -> next = malloc(sizeof(node));
                current = current -> next;
                current -> next = NULL;
                current -> suit = line[0];
                current -> face = line[1];
                current -> hidden = 1;

                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> suit == current -> suit && currentControl -> face == current -> face) {
                        if (currentControl -> hidden == 1) {
                            currentControl -> hidden = 0;
                            break;
                        } else {
                            sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is a duplicate.", lineCount, current -> suit, current -> face);
                            fclose(infile);
                            unloadCards(controlCardDeck);
                            unloadCards(cardDeck -> next);
                            cardDeck -> next = NULL;
                            return -1;
                        }
                    }
                    currentControl = currentControl -> next;
                }
                if (currentControl -> next == NULL && currentControl -> suit != current -> suit && currentControl -> face != current -> face) {
                    sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is of illegal format.", lineCount, current -> suit, current -> face);
                    fclose(infile);
                    unloadCards(controlCardDeck);
                    unloadCards(cardDeck -> next);
                    cardDeck -> next = NULL;
                    return -1;
                }
            }
            fclose(infile);
            if (lineCount != 52) {
                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> hidden == 1) {
                        sprintf(*resultMessage, "Error in savefile! There are not 52 cards as card: %c%c is missing.", currentControl -> suit, currentControl -> face);
                        unloadCards(controlCardDeck);
                        if (cardDeck -> next != NULL) {
                            unloadCards(cardDeck->next);
                        }
                        cardDeck -> next = NULL;
                        return -1;
                    }
                    currentControl = currentControl -> next;
                }
            }
        } else {
            *resultMessage = "Error. File does not exist!";
            return -1;
        }
    } else {
        insertCardDeck(cardDeck);
    }
    return 0;
}

int SD(char lastCommand[], node *cardDeck, char **resultMessage) {
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
        node* current = cardDeck -> next;
        while (current != NULL) {
            fprintf(outfile, "%c%c\n",current->suit,current->face);
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

int SW(node* cardDeck, char **resultMessage) {
    if (cardDeck -> next != NULL) {
        while (cardDeck != NULL) {
            cardDeck->hidden = 0;
            cardDeck = cardDeck->next;
        }
        return 0;
    } else {
        *resultMessage = "Error! No deck of cards are loaded.";
        return -1;
    }
}

void QQ(node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4){
    unloadCards(cardDeck);
    unloadCards(C1);
    unloadCards(C2);
    unloadCards(C3);
    unloadCards(C4);
    unloadCards(C5);
    unloadCards(C6);
    unloadCards(C7);
    unloadCards(foundation1);
    unloadCards(foundation2);
    unloadCards(foundation3);
    unloadCards(foundation4);
    exit(0);
}
void Q(int* STARTUP){
    *STARTUP = 1;
}

int P(int* STARTUP, node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4, char **resultMessage){
    if (cardDeck -> next != NULL) {

        node* newDeck = malloc(sizeof(node));
        newDeck -> next = NULL;
        node* current = cardDeck -> next;
        while (current != NULL) {
            insertElement(&newDeck, current -> suit, current -> face, 1);
            current = current -> next;
        }

        *STARTUP = 0;
        unloadCards(C1->next);
        C1->next = NULL;
        unloadCards(C2->next);
        C2->next = NULL;
        unloadCards(C3->next);
        C3->next = NULL;
        unloadCards(C4->next);
        C4->next = NULL;
        unloadCards(C5->next);
        C5->next = NULL;
        unloadCards(C6->next);
        C6->next = NULL;
        unloadCards(C7->next);
        C7->next = NULL;
        unloadCards(foundation1->next);
        foundation1->next = NULL;
        unloadCards(foundation2->next);
        foundation2->next = NULL;
        unloadCards(foundation3->next);
        foundation3->next = NULL;
        unloadCards(foundation4->next);
        foundation4->next = NULL;

        int i = 0;
        newDeck = newDeck->next;
        node *temp;
        while (newDeck != NULL) {
            temp = newDeck;
            newDeck = newDeck->next;
            if (i == 0) {
                C1->next = temp;
                C1->next->next = NULL;
            } else if ((i % 7 == 1) && i <= 36) {
                C2->next = temp;
                C2 = C2->next;
                C2->next = NULL;
            } else if ((i % 7 == 2) && i <= 44) {
                C3->next = temp;
                C3 = C3->next;
                C3->next = NULL;
            } else if ((i % 7 == 3) && i <= 52) {
                C4->next = temp;
                C4 = C4->next;
                C4->next = NULL;
            } else if ((i % 7 == 4) && i <= 60) {
                C5->next = temp;
                C5 = C5->next;
                C5->next = NULL;
            } else if ((i % 7 == 5) && i <= 68) {
                C6->next = temp;
                C6 = C6->next;
                C6->next = NULL;
            } else if ((i % 7 == 6) && i <= 76) {
                if (i >= 6 && i < 41) {
                    i++;
                } else if (i == 41) {
                    i = i + 2;
                } else if (i == 48) {
                    i = i + 3;
                } else if (i == 55) {
                    i = i + 4;
                } else if (i == 62) {
                    i = i + 5;
                } else if (i == 69) {
                    i = i + 6;
                }
                C7->next = temp;
                C7 = C7->next;
                C7->next = NULL;
            }
            i++;
        }
        return 0;
    } else {
        *resultMessage = "Error. No deck has been loaded!";
        return -1;
    }
}

void unloadCards(node* cards) {
    if (cards != NULL) {
        node *temp;
        while (cards->next != NULL) {
            temp = cards;
            cards = cards->next;
            temp->next = NULL;
            free(temp);
            temp = NULL;
        }
        cards = NULL;
    }
}

void displayEmptyBrackets(node* cardDeck){
    printf("\n\n");
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");

    int num = 1;
    if (cardDeck -> next == NULL) {
        for (int i = 1; i < 53; i++) {
            printf("  \t");
            if ((i - 7) % 14 == 0) {

                printf("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
                num++;
            }
            if (i % 7 == 0 && i != 0) {
                printf("\n");
            }
        }
    } else {
        int i = 1;
        cardDeck = cardDeck -> next;
        while (cardDeck != NULL) {
            if (cardDeck -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t",cardDeck -> suit, cardDeck -> face);
            }

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
    }

    printf("\n\n");
}

int L(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
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
            node* controlCardDeck = malloc(sizeof(node));
            controlCardDeck -> next = NULL;
            insertCardDeck(controlCardDeck);

            int lineCount = 0;
            int cardCount = 0;
            char line[5];
            int i = 0;
            node* current = C1;
            while (fgets(line, sizeof(line), infile)) {
                lineCount++;
                if (line[0] == '-') {
                    i++;
                    switch (i) {
                        case 1:
                            current = C2;
                            break;
                        case 2:
                            current = C3;
                            break;
                        case 3:
                            current = C4;
                            break;
                        case 4:
                            current = C5;
                            break;
                        case 5:
                            current = C6;
                            break;
                        case 6:
                            current = C7;
                            break;
                        case 7:
                            current = foundation1;
                            break;
                        case 8:
                            current = foundation2;
                            break;
                        case 9:
                            current = foundation3;
                            break;
                        case 10:
                            current = foundation4;
                            break;
                    }
                    continue;
                } else {
                    cardCount++;
                }
                current -> next = malloc(sizeof(node));
                current = current -> next;
                current -> next = NULL;
                current -> suit = line[0];
                current -> face = line[1];
                current -> hidden = line[2]-'0';

                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> suit == current -> suit && currentControl -> face == current -> face) {
                        if (currentControl -> hidden == 0) {
                            currentControl -> hidden = 1;
                            break;
                        } else {
                            sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is a duplicate.", lineCount, current -> suit, current -> face);
                            fclose(infile);
                            //ToDO implement unload function to unload c1, c2....
                            return -1;
                        }
                    }
                    currentControl = currentControl -> next;
                }
                if (currentControl -> next == NULL && currentControl -> suit != current -> suit && currentControl -> face != current -> face) {
                    sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is of illegal format.", lineCount, current -> suit, current -> face);
                    fclose(infile);
                    //ToDO implement unload function to unload c1, c2....
                    return -1;
                }
            }
            fclose(infile);
            if (cardCount != 52) {
                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> hidden == 0) {
                        sprintf(*resultMessage, "Error in savefile! There are not 52 cards as card: %c%c is missing.", currentControl -> suit, currentControl -> face);
                        //ToDO implement unload function to unload c1, c2....
                        return -1;
                    }
                    currentControl = currentControl -> next;
                }
            }
        } else {
            *resultMessage = "Error. File does not exist!";
            return -1;
        }
    } else {
        insertBlocks(suitStr, faceStr, C1, C2, C3, C4, C5, C6, C7);
    }
    return 0;
}

int S(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage) {
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
        outfile = fopen("saveFile.txt", "w");
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
        insertElement( &cardDeck, suitStr[i%13], faceStr[j], 1);
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

void shuffleCardsRandom(node* source, node* dist) {

    char suit[52];
    char face[52];
    char hidden[52];

    node* current = source;
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


}


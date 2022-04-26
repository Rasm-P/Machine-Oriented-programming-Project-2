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
void QQ(node* cardDeck, node* cardColumns[], node* cardFoundations[]);
void Q(int* STARTUP);
int P(int* STARTUP, node* cardDeck, node* cardColumns[], node* cardFoundations[], char **resultMessage);
void unloadCards(node* cards);
void unloadFullCardDeck(node* cardColumns[], node* cardFoundations[]);
void insertElement(node** root, char suit, char face, int hidden);
void insertCardDeck(node* cardDeck);
void displayDeck(node* cardDeck, node* cardColumns[], node* cardFoundations[], int STARTUP);
int L(char lastCommand[], node* cardColumns[], node* cardFoundations[], char **resultMessage);
int S(char lastCommand[], node* cardColumns[], node* cardFoundations[], char **resultMessage);
void insertBlocks(char suitStr[], char faceStr[], node* cardColumns[]);
void shuffleCardsRandom(node* source, node* dist);

int main() {
    node* cardDeck = malloc(sizeof(node));
    cardDeck -> next = NULL;

    node* cardColumns[7];
    for (int i = 0; i < 7; i++) {
        node* column = malloc(sizeof(node));
        column -> next = NULL;
        cardColumns[i] = column;
    }

    node* cardFoundations[4];
    for (int i = 0; i < 4; i++) {
        node* foundation = malloc(sizeof(node));
        foundation -> next = NULL;
        cardFoundations[i] = foundation;
    }

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
                result = P(&STARTUP, cardDeck, cardColumns, cardFoundations, &resultMessage);
            }  else {
                result = 1;
                resultMessage = "The chosen command does not exist in the STARTUP phase!";
            }
        } else {
            if (lastCommand[0] == 'Q') {
                Q(&STARTUP);
            }
            else if (lastCommand[0] == 'L' ) {
                result = L(lastCommand, cardColumns, cardFoundations,&resultMessage);
            }
            else if (lastCommand[0] == 'S') {
                result = S(lastCommand, cardColumns, cardFoundations, &resultMessage);
            } else {
                //Game moves
                printf("TO DO!\n");
            }
        }
        if (lastCommand[0] == 'Q' && lastCommand[1] == 'Q') {
            printf("Thank you for playing!\n");
            QQ(cardDeck, cardColumns, cardFoundations);
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
        displayDeck(cardDeck, cardColumns, cardFoundations, STARTUP);
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

void QQ(node* cardDeck, node* cardColumns[], node* cardFoundations[]){
    unloadCards(cardDeck);
    unloadFullCardDeck(cardColumns, cardFoundations);
    exit(0);
}

void Q(int* STARTUP){
    *STARTUP = 1;
}

int P(int* STARTUP, node* cardDeck, node* cardColumns[7], node* cardFoundations[4], char **resultMessage){
    if (cardDeck -> next != NULL) {

        node* newDeck = malloc(sizeof(node));
        newDeck -> next = NULL;
        node* current = cardDeck -> next;
        while (current != NULL) {
            insertElement(&newDeck, current -> suit, current -> face, 1);
            current = current -> next;
        }

        *STARTUP = 0;
        for (int i = 0; i < 7; i++) {
            unloadCards(cardColumns[i] ->next);
            cardColumns[i] -> next = NULL;
        }
        for (int i = 0; i < 4; i++) {
            unloadCards(cardFoundations[i] ->next);
            cardFoundations[i] -> next = NULL;
        }

        int i = 0;
        newDeck = newDeck->next;
        node *temp;
        while (newDeck != NULL) {
            temp = newDeck;
            newDeck = newDeck->next;
            if (i == 0) {
                cardColumns[0]->next = temp;
                cardColumns[0]->next->hidden = 0;
                cardColumns[0]->next->next = NULL;
            } else if ((i % 7 == 1) && i <= 36) {
                cardColumns[1]->next = temp;
                cardColumns[1] = cardColumns[1]->next;
                if (i>=8) {
                    cardColumns[1]->hidden=0;
                }
                cardColumns[1]->next = NULL;
            } else if ((i % 7 == 2) && i <= 44) {
                cardColumns[2]->next = temp;
                cardColumns[2] = cardColumns[2]->next;
                if (i>=16) {
                    cardColumns[2]->hidden=0;
                }
                cardColumns[2]->next = NULL;
            } else if ((i % 7 == 3) && i <= 52) {
                cardColumns[3]->next = temp;
                cardColumns[3] = cardColumns[3]->next;
                if (i>=24) {
                    cardColumns[3]->hidden=0;
                }
                cardColumns[3]->next = NULL;
            } else if ((i % 7 == 4) && i <= 60) {
                cardColumns[4]->next = temp;
                cardColumns[4] = cardColumns[4]->next;
                if (i>=32) {
                    cardColumns[4]->hidden=0;
                }
                cardColumns[4]->next = NULL;
            } else if ((i % 7 == 5) && i <= 68) {
                cardColumns[5]->next = temp;
                cardColumns[5] = cardColumns[5]->next;
                if (i>=40) {
                    cardColumns[5]->hidden=0;
                }
                cardColumns[5]->next = NULL;
            } else if ((i % 7 == 6) && i <= 76) {
                cardColumns[6]->next = temp;
                cardColumns[6] = cardColumns[6]->next;
                if (i>=48) {
                    cardColumns[6]->hidden=0;
                }
                cardColumns[6]->next = NULL;
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

void unloadFullCardDeck(node* cardColumns[], node* cardFoundations[]) {
    for (int i = 0; i < 7; i++) {
        unloadCards(cardColumns[i] -> next);
        cardColumns[i] -> next = NULL;
    }
    for (int i = 0; i < 4; i++) {
        unloadCards(cardFoundations[i] -> next);
        cardFoundations[i] -> next = NULL;
    }
}

void displayDeck(node* cardDeck, node* cardColumns[], node* cardFoundations[], int STARTUP){
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
    } else if (!STARTUP) {
        int i = 0;
        while(cardColumns[0] != NULL || cardColumns[1] != NULL || cardColumns[2] != NULL || cardColumns[3] != NULL || cardColumns[4] != NULL || cardColumns[5] != NULL || cardColumns[6] != NULL) {
            for (int j = 0; j < 7; j++) {
                if (cardColumns[j] != NULL) {
                    cardColumns[j] = cardColumns[j]->next;
                }
                if (cardColumns[j] == NULL) {
                    printf("  \t");
                } else if (cardColumns[j] -> hidden == 1) {
                    printf("%c%c\t", '[', ']');
                } else {
                    printf("%c%c\t",cardColumns[j] -> suit, cardColumns[j] -> face);
                }
            }
            i = i+7;
            if ((i - 7) % 14 == 0 && i<=55) {
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

int L(char lastCommand[], node* cardColumns[], node* cardFoundations[], char **resultMessage) {
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
            unloadFullCardDeck(cardColumns, cardFoundations);
            node* controlCardDeck = malloc(sizeof(node));
            controlCardDeck -> next = NULL;
            insertCardDeck(controlCardDeck);
            int lineCount = 0;
            int cardCount = 0;
            char line[5];
            int i = 0;
            node* current = cardColumns[0];
            while (fgets(line, sizeof(line), infile)) {
                lineCount++;
                if (line[0] == '-') {
                    i++;
                    switch (i) {
                        case 1:
                            current = cardColumns[1];
                            break;
                        case 2:
                            current = cardColumns[2];
                            break;
                        case 3:
                            current = cardColumns[3];
                            break;
                        case 4:
                            current = cardColumns[4];
                            break;
                        case 5:
                            current = cardColumns[5];
                            break;
                        case 6:
                            current = cardColumns[6];
                            break;
                        case 7:
                            current = cardFoundations[0];
                            break;
                        case 8:
                            current = cardFoundations[1];
                            break;
                        case 9:
                            current = cardFoundations[2];
                            break;
                        case 10:
                            current = cardFoundations[3];
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
                            unloadCards(controlCardDeck);
                            unloadFullCardDeck(cardColumns, cardFoundations);
                            return -1;
                        }
                    }
                    currentControl = currentControl -> next;
                }
                if (currentControl -> next == NULL && currentControl -> suit != current -> suit && currentControl -> face != current -> face) {
                    sprintf(*resultMessage, "Error in savefile at line %d! Card: %c%c is of illegal format.", lineCount, current -> suit, current -> face);
                    fclose(infile);
                    unloadCards(controlCardDeck);
                    unloadFullCardDeck(cardColumns, cardFoundations);
                    return -1;
                }
            }
            fclose(infile);
            if (cardCount != 52) {
                node* currentControl = controlCardDeck;
                while (currentControl -> next != NULL) {
                    if (currentControl -> hidden == 0) {
                        sprintf(*resultMessage, "Error in savefile! There are not 52 cards as card: %c%c is missing.", currentControl -> suit, currentControl -> face);
                        unloadCards(controlCardDeck);
                        unloadFullCardDeck(cardColumns, cardFoundations);
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
        insertBlocks(suitStr, faceStr, cardColumns);
    }
    return 0;
}

int S(char lastCommand[], node* cardColumns[], node* cardFoundations[], char **resultMessage) {
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
        for (int i = 0; i < 7; i++) {
            current = cardColumns[i] -> next;
            while (current != NULL) {
                fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
                current = current -> next;
            }
            fprintf(outfile,"-\n");
        }
        for (int i = 0; i < 4; i++) {
            current = cardFoundations[i] -> next;
            while (current != NULL) {
                fprintf(outfile, "%c%c%d\n",current->suit,current->face,current->hidden);
                current = current -> next;
            }
            if (i < 3) {
                fprintf(outfile, "-\n");
            }
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

void insertBlocks(char suitStr[], char faceStr[], node* cardColumns[]) {
    int k = 51;
    int i = 0;
    int j = 0;
    while ( i < 52 ) {
        for (int g = 0; g < 7; g++) {
            insertElement( &cardColumns[g], suitStr [i % 13], faceStr [j], 0);
            i++;

            if (i > k) {
                break;
            } else if (i % 13 == 0) {
                j++;
            }
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


#include "header.h"
#include <stdlib.h>
#include <stdio.h>


void displayDeck(node* cardDeck, node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, int STARTUP){
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
        while(C1 != NULL || C2 != NULL || C3 != NULL || C4 != NULL || C5 != NULL || C6 != NULL || C7 != NULL) {
            if (C1 != NULL) {
                C1 = C1->next;
            }
            if (C1 == NULL) {
                printf("  \t");
            } else if (C1 -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t", C1 -> face, C1 -> suit);
            }
            if (C2 != NULL) {
                C2 = C2->next;
            }
            if (C2 == NULL) {
                printf("  \t");
            } else if (C2 -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t", C2 -> face, C2 -> suit);
            }
            if (C3 != NULL) {
                C3 = C3->next;
            }
            if (C3 == NULL) {
                printf("  \t");
            } else if (C3 -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t", C3 -> face, C3 -> suit);
            }
            if (C4 != NULL) {
                C4 = C4->next;
            }
            if (C4 == NULL) {
                printf("  \t");
            } else if (C4 -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t", C4 -> face, C4 -> suit);
            }
            if (C5 != NULL) {
                C5 = C5->next;
            }
            if (C5 == NULL) {
                printf("  \t");
            } else if (C5 -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t", C5 -> face, C5 -> suit);
            }
            if (C6 != NULL) {
                C6 = C6->next;
            }
            if (C6 == NULL) {
                printf("  \t");
            } else if (C6 -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t", C6 -> face, C6 -> suit);
            }
            if (C7 != NULL) {
                C7 = C7->next;
            }
            if (C7 == NULL) {
                printf("  \t");
            } else if (C7 -> hidden == 1) {
                printf("%c%c\t", '[', ']');
            } else {
                printf("%c%c\t", C7 -> face, C7 -> suit);
            }
            i = i+7;
            if ((i - 7) % 14 == 0 && i<=55) {
                if (num == 1) {
                    if (foundation1->next == NULL) {
                        printf("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
                    } else {
                        node *last = foundation1->next;
                        while (last -> next != NULL) {
                            last = last -> next;
                        }
                        printf("\t\t\t%c%c\t%c%d", last -> face, last -> suit, 'F', num);
                    }
                } else if (num == 2) {
                    if (foundation2->next == NULL) {
                        printf("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
                    } else {
                        node *last = foundation2->next;
                        while (last -> next != NULL) {
                            last = last -> next;
                        }
                        printf("\t\t\t%c%c\t%c%d", last -> face, last -> suit, 'F', num);
                    }
                } if (num == 3) {
                    if (foundation3->next == NULL) {
                        printf("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
                    } else {
                        node *last = foundation3->next;
                        while (last -> next != NULL) {
                            last = last -> next;
                        }
                        printf("\t\t\t%c%c\t%c%d", last -> face, last -> suit, 'F', num);
                    }
                } if (num == 4) {
                    if (foundation4->next == NULL) {
                        printf("\t\t\t%c%c\t%c%d", '[', ']', 'F', num);
                    } else {
                        node *last = foundation4->next;
                        while (last -> next != NULL) {
                            last = last -> next;
                        }
                        printf("\t\t\t%c%c\t%c%d", last -> face, last -> suit, 'F', num);
                    }
                }
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
            printf("%c%c\t", '[', ']');
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
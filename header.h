#ifndef _INC_HEADER
#define _INC_HEADER


#define COMMAND_STRING 30
#define MAX_STRING 120

typedef struct node {
    char suit;
    char face;
    int hidden;
    struct node* next;
}node;

int SD(char lastCommand[], node *cardDeck, char **resultMessage);
int SW(node* cardDeck, char **resultMessage);
int LD(char lastCommand[], node *cardDeck, char **resultMessage);
void QQ(node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4);
void Q(int* STARTUP);
int P(int* STARTUP, node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4, char **resultMessage);
void unloadCards(node* cards);
void unloadFullCardDeck(node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4);
void insertElement(node** root, char suit, char face, int hidden);
void insertCardDeck(node* cardDeck);
void displayDeck(node* cardDeck, node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, int STARTUP);
int L(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage);
int S(char lastCommand[], node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7, node *foundation1, node *foundation2, node *foundation3, node *foundation4, char **resultMessage);
void insertBlocks(char suitStr[], char faceStr[], node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7);
void shuffleCardsRandom(node* source);
void print_list(node* head);
int splitDeck(char lastCommand[], node* source, char **resultMessage);

#endif
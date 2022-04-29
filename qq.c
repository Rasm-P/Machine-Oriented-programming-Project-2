#include <stdlib.h>
#include "header.h"


void QQ(node* cardDeck, node* C1, node* C2, node* C3, node* C4, node* C5, node* C6, node* C7, node* foundation1, node* foundation2, node* foundation3, node* foundation4){
    unloadCards(cardDeck);
    unloadFullCardDeck(C1, C2, C3, C4, C5, C6, C7, foundation1, foundation2, foundation3, foundation4);
    exit(0);
}
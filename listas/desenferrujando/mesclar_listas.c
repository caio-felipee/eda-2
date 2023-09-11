#include <stdio.h>

typedef struct celula {
    int dado;   
    struct celula *prox;
} celula;

void mescla_listas(celula *l1, celula *l2, celula *l3) {
    celula *curr = l3;
    l1 = l1->prox;
    l2 = l2->prox;

    while(l1 != NULL && l2 != NULL) {
        if(l1->dado <= l2->dado) {
            curr->prox = l1;
            l1 = l1->prox;
            curr = curr->prox;
        }
        else {
            curr->prox = l2;
            l2 = l2->prox;
            curr = curr->prox;
        }
    }

    while(l1 != NULL) {
        curr->prox = l1;
        l1 = l1->prox;
        curr = curr->prox;
    }

    while(l2 != NULL) {
        curr->prox = l2;
        l2 = l2->prox;
        curr = curr->prox;
    }

    curr->prox = NULL;
}
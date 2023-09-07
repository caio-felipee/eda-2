#include <stdio.h>

typedef struct celula {
    char matricula[10];
    double mediaAtividades;
    double mediaProvas;
    struct celula *prox;
} celula;

void relatorioMediaAtividades (celula *le, celula *l1, celula *l2, double media) {
    int first1 = 0, first2 = 0, i = 0;

    while(le->prox != NULL) {
        if(le->mediaAtividades <= media) {
            l1->prox = le;
        }
        else {
            l2->prox = le;
        }
        
        le = le->prox;
    }

    l1->prox = NULL;
    l2->prox = NULL;        
}
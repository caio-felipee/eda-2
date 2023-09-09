#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    char matricula[10];
    double mediaAtividades;
    double mediaProvas;
    struct celula *prox;
} celula;

void relatorioMediaAtividades (celula *le, celula *l1, celula *l2, double media) {
    celula *l1v = l1, *l2v = l2;
    while(le->prox != NULL) {
        le = le->prox;

        if(le->mediaAtividades <= media) {
            l1v->prox = le;
            l1v = l1v->prox;
        }
        else {
            l2v->prox = le;
            l2v = l2v->prox;
        }        
    }

    l1v->prox = NULL;
    l2v->prox = NULL;        
}
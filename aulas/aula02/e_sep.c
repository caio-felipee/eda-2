#include <stdlib.h>
#include <stdbool.h>

#define TAM 3000
#define KEY(a) a.key
#define HASH(key, m) key % m
#define NULLitem -1
#define STEP 10
#define EQ(a, b) KEY(a) == KEY(b)

typedef struct Item {
    int key;
} Item;

typedef struct node
{
    Item item;
    node *next;
} node;

node *HTinit(int M) { // Iniciando a Hash Table
    node *ht = malloc(sizeof(node) * M);

    for(int i = 0; i < M; i++)
        ht[i].next = NULL;
    
    return ht;
}

bool insert(node *ht, int M, Item newitem) {
    int h = HASH(KEY(newitem), M);

    node *aux = ht[h].next; 
    /* O primeiro elemento da lista encadeada
    * é como se fosse a minha "head". 
    * Portanto, não assumirá um valor!
    */

    while(aux != NULL) {
        if(EQ(aux->item, newitem)) {
            return true;
        }

        aux = aux->next;
    }

    aux = malloc(sizeof(node));
    aux->item = newitem;
    aux->next = ht[h].next;
    ht[h].next = aux;
}
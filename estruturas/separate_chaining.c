#include <stdio.h>
#include <stdbool.h>

#define M 31849
#define KEY(A) A % M
#define STEP 10

typedef int Item;
typedef struct node {
    struct node *next;
    Item value;
} node;

bool search(node *hash, Item item) {
    int key = KEY(item), i = 0;
    node aux = hash[key];

    while(aux.next != NULL && i++ < STEP) {
        aux = *aux.next;

        if(aux.value == item)
            return true;
    }

    return false;
}

void insert(node *hash, Item item) {
    node *value = malloc(sizeof(Item));
    int key = KEY(item);

    if(search(value, item))
        return;

    value->next = hash[key].next;
    hash[key].next = value;
}

int main() {
    node *hash = malloc(sizeof(node)*M);
    
}
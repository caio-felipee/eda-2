#include <stdio.h>
#include <stdbool.h>

typedef int Item;
typedef struct Linked_List {
    Item value;
    struct Linked_List *next;
} Linked_List;

typedef struct Queue {
    int size;
    Linked_List *first;
    Linked_List *last;
} Queue;

bool is_empty(Queue *q) {
    return q->size == 0;
}

Linked_List *create_item(Item item) {
    Linked_List *new = malloc(sizeof(Linked_List));
    new->value = item;
    new->next = NULL;

    return new;
}

void insert(Queue *q, Item item) {
    Linked_List *value = create_item(item);

    q->size++;

    if(q->first == NULL) {
        q->first = value;
        q->last = value;
        return;
    }

    q->last->next = value;
    q->last = value;
}

Item *front(Queue *q) {
    if(is_empty(q))
        return NULL;
    
    return q->first;
}

void pop(Queue *q) {
    if(is_empty(q))
        return;
    
    Linked_List *next = q->first->next;
    free(q->first);
    q->first = next;
    q->size--;
}

Queue *init_queue() {
    Queue *q = malloc(sizeof(Queue));
    q->size = 0;
    q->first = NULL;
    q->last = NULL;

    return q;
}
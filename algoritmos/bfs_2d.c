#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define less_rb(A, B) (A.x == B.x ? A.y < B.y : A.x < B.x)

typedef struct Item {
    int x, y, dist;
} Item;

typedef struct Linked_List {
    Item value;
    struct Linked_List *next;
} Linked_List;

typedef struct Queue {
    int size;
    Linked_List *first;
    Linked_List *last;
} Queue;

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

bool is_empty(Queue *q) {
    return q->size == 0;
}

Item front(Queue *q) {    
    return q->first->value;
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

int dist(int x1, int y1, int x2, int y2) {
    return (int)ceil(sqrt((double)((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2))));
}

int bfs(Linked_List *adj, int sx, int sy, int ex, int ey, int md) {
    Queue *q = init_queue();
    insert(q, (Item){sx, sy});

    while(!is_empty(q)) {
        Item f = front(q);
        pop(q);
        Linked_List *tmp = adj;
        while(tmp->next != NULL) {
            tmp = tmp->next;

            if(tmp->value.dist != -1 && dist(tmp->value.x, tmp->value.y, f.x, f.y) <= md) {
                if(tmp->value.x == ex && tmp->value.y == ey)
                    return f.dist + 1;
                
                tmp->value.dist = -1;
                insert(q, (Item){tmp->value.x, tmp->value.y, f.dist + 1});
            }

        }
    }

    return -1;
}
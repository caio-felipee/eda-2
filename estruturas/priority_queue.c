#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define value(A) A.value
#define higher(A, B) A.priority > B.priority
#define less(A, B) A.priority < B.priority

typedef struct Item {
    int value;
    int priority;
} Item;

typedef struct Priority_Queue {
    Item *array;
    int size;
    int last;
} Priority_Queue;

void swap(Item *a, Item *b) {
  Item temp = *b;
  *b = *a;
  *a = temp;
}

/* 
* Priority Queue com o 1 indexado
*/

Priority_Queue *init_pq(int size) {
    Priority_Queue *pq = malloc(sizeof(Priority_Queue));    
    pq->size = 0;
    pq->last = 1;
    pq->array = malloc(sizeof(Item)*(size + 1));

    return pq;
}

void up_heap(Priority_Queue *pq, int k) {
    Item v = pq->array[k];

    while(k > 1 && less(pq->array[k / 2], v)) {
        pq->array[k] = pq->array[k / 2];
        k /= 2;
    }

    pq->array[k] = v;
}

void down_heap(Priority_Queue *pq) {
    int k = 1, n = pq->last - 1, j;
    Item v = pq->array[k];

    while(k <= n / 2) {
        j = k * 2;
        if(j < n && less(pq->array[j], pq->array[j + 1])) j++;
        if(higher(v, pq->array[j])) break;
        pq->array[k] = pq->array[j];
        k = j;
    }

    pq->array[k] = v;
}

void insert(Priority_Queue *pq, Item item) {
    pq->array[pq->last] = item;
    up_heap(pq, pq->last++);
}

void pop(Priority_Queue *pq) {
    swap(&pq->array[pq->last - 1], &pq->array[1]);
    pq->last--;
    down_heap(pq);
}

Item top(Priority_Queue *pq) {
    return pq->array[1];
}

bool is_empty(Priority_Queue *pq) {
    return pq->last == 1;
}

int main() {
    Priority_Queue *pq = init_pq(100);
    insert(pq, (Item){10, 10});
    printf("%d\n", top(pq).value);

    insert(pq, (Item){15, 15});
    printf("%d\n", top(pq).value);

    insert(pq, (Item){5, 5});
    printf("%d\n", top(pq).value);
    
    pop(pq);
    printf("%d\n", top(pq).value);

    pop(pq);
    printf("%d\n", top(pq).value);
}
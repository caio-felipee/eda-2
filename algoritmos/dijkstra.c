#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX ((int)1e6 + 10)
#define Graph Linked_List
#define value(A) A.value
#define higher(A, B) A.priority > B.priority
#define less(A, B) A.priority < B.priority
#define oo ((int)1e6 + 10)

typedef struct Linked_List {
    int weight;
    int value;
    struct Linked_List *next;
} Linked_List;


typedef struct Item {
    int value;
    int weight;
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

    while(k > 1 && higher(pq->array[k / 2], v)) {
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
        if(j < n && higher(pq->array[j], pq->array[j + 1])) j++;
        if(less(v, pq->array[j])) break;
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

Linked_List *create_item(int item) {
    Linked_List *new = malloc(sizeof(Linked_List));
    new->value = item;
    new->next = NULL;

    return new;
}

Graph *init_graph(int size) {
    Graph *graph = malloc(sizeof(Graph)*size);
    
    for(int i = 0; i < size; i++) {
        graph[i].value = 0;
        graph[i].next = NULL;
    }

    return graph;
}

void push(Graph *graph, int a, int b, int w) {
    Linked_List *item = malloc(sizeof(Linked_List));
    item->value = b;
    item->next = graph[a].next;
    item->weight = w;

    graph[a].next = item;
}

int *dijkstra(Graph *graph, int s, int N) {
    bool visited[N + 1];
    memset(visited, false, N + 1);

    int *dist = malloc(sizeof(int)*(N + 1));

    for(int i = 0; i <= N; i++)
        dist[i] = oo;
    
    Priority_Queue *pq = init_pq(MAX);
    insert(pq, (Item){ s, 0, 0 });
    dist[s] = 0;

    while(!is_empty(pq)) {
        Item t = top(pq);
        pop(pq);

        if(visited[t.value])
            continue;
        
        visited[t.value] = true;
 
        Graph tmp = graph[t.value];
        while(tmp.next != NULL) {
            tmp = *tmp.next;

            if(dist[tmp.value] > dist[t.value] + tmp.weight)
                dist[tmp.value] = dist[t.value] + tmp.weight;

            if(!visited[tmp.value]) {
                insert(pq, (Item){ tmp.value, dist[tmp.value], dist[tmp.value] });
            }
        }
    }

    free(pq);
    return dist;
}

int main() {
    Graph *graph = init_graph(9);

    push(graph, 1, 2, 2);
    push(graph, 2, 1, 2);
    push(graph, 2, 3, 1);
    push(graph, 3, 2, 1);
    push(graph, 3, 1, 5);
    push(graph, 1, 3, 5);
    push(graph, 3, 5, 100);
    push(graph, 5, 3, 100);
    push(graph, 2, 6, 7);
    push(graph, 6, 2, 7);
    push(graph, 1, 7, 9);
    push(graph, 7, 1, 9);
    push(graph, 3, 8, 7);
    push(graph, 8, 3, 7);

    int *dist = dijkstra(graph, 1, 8);

    for(int i = 1; i <= 8; i++) {
        printf("Dist %d: %d\n", i, dist[i]);
    }

    return 0;
}
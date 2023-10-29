// Ir e vir

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX ((int)1e6 + 10)
#define Graph Linked_List

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

Graph *init_graph(int size) {
    Graph *graph = malloc(sizeof(Graph)*size);
    
    for(int i = 0; i < size; i++) {
        graph[i].value = 0;
        graph[i].next = NULL;
    }

    return graph;
}

void push(Graph *graph, int a, int b) {
    Linked_List *item = malloc(sizeof(Linked_List));
    item->value = b;
    item->next = graph[a].next;

    graph[a].next = item;
}

int bfs(Graph *graph, bool *visited, int s, int n) {
    for(int i = 1; i <= n; i++) {
        visited[i] = false;
    }

    Queue *queue = init_queue();
    insert(queue, s);
    visited[s] = true;
    int v = 0;

    while(!is_empty(queue)) {
        Item f = front(queue);
        pop(queue);
        v++;

        Graph tmp = graph[f];
        while(tmp.next != NULL) {
            tmp = *tmp.next;

            if(!visited[tmp.value]) {
                visited[tmp.value] = true;
                insert(queue, tmp.value);
            }
        }
    }

    return v;
}

int solve(int n, int m) {
    Graph *graph = init_graph(n + 1);
    bool visited[n + 1];

    Queue *one_way = init_queue();
    int a, b, p;
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &p);

        push(graph, a, b);

        if(p >= 2)
            push(graph, b, a);
        else
            insert(one_way, b);
    }

    if(is_empty(one_way)) {
        int v = bfs(graph, visited, 1, n);

        return (v == n ? 1 : 0);
    }

    while(!is_empty(one_way)) {
        int f = front(one_way);
        pop(one_way);

        int v = bfs(graph, visited, f, n);
        if(v < n)
            return 0;
    }

    return 1;
}

int main() {
    int n, m;

    while(scanf("%d %d", &n, &m) != EOF && n > 0) {
        printf("%d\n", solve(n, m));
    }

    return 0;
}
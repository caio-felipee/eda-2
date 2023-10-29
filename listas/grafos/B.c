// Estradas asfaltadas - O início

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

Graph *init_graph() {
    Graph *graph = malloc(sizeof(Graph)*MAX);
    
    for(int i = 0; i < MAX; i++) {
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

void bfs(Graph *graph, bool *visited, int s) {
    Queue *queue = init_queue();
    insert(queue, s);
    visited[s] = true;

    while(!is_empty(queue)) {
        Item f = front(queue);
        pop(queue);

        Graph tmp = graph[f];
        while(tmp.next != NULL) {
            tmp = *tmp.next;

            if(!visited[tmp.value]) {
                visited[tmp.value] = true;
                insert(queue, tmp.value);
            }
        }
    }
}

int main() {
    Graph *graph = init_graph();
    bool visited[MAX];
    
    for(int i = 0; i < MAX; i++) {
        visited[i] = false;
    }

    int n, a, b, ans = 0;
    scanf("%d", &n);

    while(scanf("%d %d", &a, &b) != EOF) {
        push(graph, a, b);
        push(graph, b, a);
    }

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            ans++;
            bfs(graph, visited, i);
        }
    }

    printf("%d\n", ans);    

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX ((int)1e6 + 10)
#define Graph Linked_List
#define MOD 315931

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

typedef struct node {
    struct node *next;
    int value;
    char *name;
} node;

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

int bfs(Graph *graph, bool *visited, int s) {
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

int key(char *value) 
{
    int a = 314159;
    int b = 271828;
    int h = 1;

    for(; *value != 0; value++) 
    {
        a = (a + b *(*value)) % MOD;
        h = (h*a) % MOD; 
    }

    return h < 0 ? h + MOD : h;
}

bool is_equal(char *str1, char *str2) {
    int i;
    for(i = 0; str1[i] != 0 && str2[i] != 0; i++) {
        if(str1[i] != str2[i])
            return false;
    }

    return str1[i] == str2[i];
}

node *search(node *hash, char *item) {
    int k = key(item);
    node aux = hash[k];

    while(aux.next != NULL) {
        // printf("search %s %s\n", aux.next->name, item);
        if(is_equal(aux.next->name, item))
            return aux.next;

        aux = *aux.next;
    }

    return NULL;
}

void ht_insert(node *hash, char *item, int nv) {
    int k = key(item);

    node *s = search(hash, item);

    if(s == NULL) {
        node *value = malloc(sizeof(node));
        value->name = item;
        value->value = nv;
        value->next = hash[k].next;
        hash[k].next = value;
    }
    else {
        s->value = nv;
    }
}

void solve(int n, int m) {
    node *ht = malloc(sizeof(node) * MOD);
    Graph *graph = init_graph(n + 1);
    bool visited[n + 1];

    for(int i = 1; i <= n; i++)
        visited[i] = false;

    char str[31];
    for(int i = 1; i <= n; i++) {
        scanf(" %s", str);

        char *name = malloc(sizeof(char)*31);
        strcpy(name, str);

        ht_insert(ht, name, i);
    }

    char str2[31];

    for(int i = 0; i < m; i++) {
        scanf(" %s %s", str, str2);

        int f = search(ht, str)->value, s = search(ht, str2)->value;
        push(graph, f, s);
        push(graph, s, f);

    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(visited[i])
            continue;
        
        int v = bfs(graph, visited, i);
        ans = v > ans ? v : ans;
    }

    printf("%d\n", ans);
}

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF && n)
        solve(n, m);
    
    return 0;
}
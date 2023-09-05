#include <stdlib.h>
#include <stdbool.h>

typedef struct Item {
    int key;
} Item;

#define TAM 3000
#define KEY(a) a.key
#define HASH(key, m) key % m
#define NULLitem -1
#define STEP 10
#define EQ(a, b) KEY(a) == KEY(b)

int htfind(Item *ht, int M, Item vs) {
    int key = KEY(vs);
    int h = HASH(key, M);

    for(int c = 0, i = h; c < STEP; i = (i + 1)%M, c++) {
        if(EQ(ht[i], vs))
            return i;
    }

    return -1;
}

bool insert(Item *ht, int M, Item novo) {
    int h = HASH(KEY(novo), M);
    int find = htfind(ht, M, novo);
    int c = 0;

    if(find) {
        ht[find] = novo;
        return true;
    }

    while(KEY(ht[h]) != NULLitem && c++ <= STEP)
        h = (h + 1) % M;

    if(c > STEP)
        return false;

    ht[h] = novo;
    return true;
}

int main() {
    Item *hashtable = malloc(sizeof(Item) * TAM);

    // Set all items null
    for(int i = 0; i < TAM; i++)
        hashtable[i] = (Item){NULLitem};
    
    // Implementar a função de inserção sem funçar a função de busca como apoio
}
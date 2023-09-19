// Mensagens Nlogoniences

#include <stdio.h>
#include <stdlib.h>

#define MAX (int)1e7 + 19
#define HASH(key) key % MAX
#define less(A, B) A.pos, B.pos

typedef struct Pair {
    int pos;
    char val;
} Pair;

typedef Pair Item;
void merge(Item *vs, int l, int mid, int r)
{
    Item *v = malloc(sizeof(Item)*(r - l + 1));
    int i = l, j = mid + 1, k = 0;

    while(i <= mid && j <= r) 
    {
        if(less(vs[i], vs[j]))
            v[k++] = vs[i++];
        else
            v[k++] = vs[j++];
    }

    while(i <= mid)
        v[k++] = vs[i++];
    
    while(j <= r)
        v[k++] = vs[j++];
    
    k = 0;
    for(i = l; i <= r; i++)
        vs[i] = v[k++];
    
    free(v);
}

void mergesort(Item *vs, int l, int r)
{
    if(l >= r)
        return;
    
    int mid = l + (r - l)/2;
    mergesort(vs, l, mid);
    mergesort(vs, mid + 1, r);
    merge(vs, l, mid, r);
}

Pair *left_shift(Pair *vs, int *max) {
    Pair *v = malloc(sizeof(Pair)*(*max) + 1);
    int l = 0;

    for(int i = 0; i <= *max; i++) {
        if(vs[i].val > 0)
            v[l++] = vs[i];
    }

    *max = l - 1;
    free(vs);
    return v;
}

int main() {
    Pair *hash = calloc(MAX, sizeof(Pair));
    int p, r = 0;
    char c;

    while(scanf(" %d %c", &p, &c) != EOF) {
        hash[HASH(p)] = (Pair){p, c};
        r = HASH(p) > r ? HASH(p) : r;
    }

    Pair *vs = left_shift(hash, &r);
    mergesort(vs, 0, r);

    for(int i = 0; i <= r; i++) {
        printf("%c", vs[i].val);
    }
    
    printf("\n");
}
// Classificado de sementes

#include <stdio.h>
#include <stdlib.h>

#define swap(A, B) Item t = A; A = B; B = t;
#define less(A, B) A.code < B.code

typedef long long ll;
typedef struct Item {
    ll code, quality;
} Item;

int less_quick(Item a, Item b) {
    return a.quality == b.quality ? a.code < b.code : a.quality < b.quality;
}

int partition(Item *array, int l, int r) {
    Item pivot = array[r];
    int i = l - 1, j = r;

    while(1) {
        while(less_quick(array[++i], pivot));
        while(less_quick(pivot, array[--j])) if(j == l) break;

        if(i >= j)
            break;
            
        swap(array[i], array[j]);
    }

    swap(array[i], array[r]);
    return i;
}

void quick_select(Item *array, int l, int r, int k) {
    if(r <= l)
        return;

    int index = partition(array, l, r);

    if(index > k)
        quick_select(array, l, index - 1, k);
    else if(index < k)
        quick_select(array, index + 1, r, k);
}

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

int main() {
    Item *vs = malloc(sizeof(Item)*((int)1e7 + 1));
    ll k, code, quality, i = 0;
    scanf("%lld", &k);

    while(scanf("%lld %lld", &code, &quality) != EOF) {
        vs[i++] = (Item){code, quality};
    }

    quick_select(vs, 0, i - 1, k);
    mergesort(vs, 0, k - 1);

    for(int j = 0; j < k; j++) {
        printf("%lld %lld\n", vs[j].code, vs[j].quality);
    }
}
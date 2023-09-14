#include <stdio.h>
#include <stdlib.h>

typedef int Item;
void merge(Item *vs, int l, int mid, int r)
{
    Item *v = malloc(sizeof(Item)*(r - l + 1));
    int i = l, j = mid + 1, k = 0;

    while(i <= mid && j <= r) 
    {
        if(less(vs[i], vs[j]) || eq(vs[i], vs[j]))
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
#include <stdio.h>
#include <stdlib.h>

const int MAX = 101010;

#define key(A) A.amount
#define less(A, B) key(A) < key(B)

typedef struct Item
{
    char ch;
    int amount;
    int start;
} Item;

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

int main()
{
    Item *values = malloc(sizeof(Item)*MAX);
    char tmp;
    int index = 0, i = 0;

    scanf("%c", &tmp);
    values[0].ch = tmp;
    values[0].amount = 1;
    values[0].start = 0;

    while(scanf("%c", &tmp) && tmp != '\n')
    {
        ++index;

        if(tmp == values[i].ch) 
        {
            values[i].amount++;
        }

        else
        {
            values[++i].amount = 1;
            values[i].start = index;
            values[i].ch = tmp;
        }
    }

    mergesort(values, 0, i);

    for(int j = i; j >= 0; j--)
        printf("%d %c %d\n", values[j].amount, values[j].ch, values[j].start);
}
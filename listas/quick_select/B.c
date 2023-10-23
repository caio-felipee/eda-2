// kk-página

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef int Item;
#define swap(A, B) Item t = A; A = B; B = t;
#define value(A) A
#define lesseq(A, B) value(A) <= value(B)
#define less(A, B) A < B
#define higher(A, B) A > B

Item partition(Item *array, int l, int r) {
    Item x = array[r], i = l;
    for(int j = l; j < r; j++) {
        if(lesseq(array[j], x)) {
            swap(array[i], array[j]);
            i++;
        }
    }

    swap(array[i], array[r]);
    return i;
}

int rand_partition(Item *array, int low, int high)
{
    srand(time(0));
    int random = low + rand() % (high - low);
 
    Item temp = array[random];
    array[random] = array[low];
    array[low] = temp;
    
    return partition(array, low, high);
}

void quick_select(Item *array, int l, int r, int k) {
    if(r <= l)
        return;
    
    int index = rand_partition(array, l, r);

    // if(index == k)
    //     return array[index];
    
    if(index > k)
        return quick_select(array, l, index - 1, k);
    
    return quick_select(array, index + 1, r, k);
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
    int n, p, x, i = 0;
    scanf("%d %d %d", &n, &p, &x);

    Item *array = malloc(sizeof(Item) * n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    int size = x * (p + 1) - 1;

    if(size > n - 1)
        size = n - 1;

    int first = p * x;
    /*
    * O quick select retorna a garantia que o k-th número é o maior entre os que estão no intervalo.
    * Logo, posso fazer a otimização utilizando dois quick-select.
    */
    quick_select(array, 0, n - 1, size);
    quick_select(array, 0, size, first);
    mergesort(array, first, size);

    for(int i = first; i <= size; i++) {
        printf("%d\n", array[i]);
    }
}
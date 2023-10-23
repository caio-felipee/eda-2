#include <stdio.h>

typedef int Item;
#define swap(A, B) Item t = A; A = B; B = t;
#define less_quick(A, B) A < B

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

int main() {
    Item arr[] = {34, 3, 43, 5, 9, 7, 11, 45, 99};
    int k = 3;
    quick_select(arr, 0, 8, k);

    for(int i = 0; i < k; i++)
        printf("%d\n", arr[i]);
}
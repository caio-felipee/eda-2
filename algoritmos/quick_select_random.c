#include <stdio.h>
#include <time.h>

typedef int Item;
#define swap(A, B) Item t = A; A = B; B = t;
#define value(A) A
#define lesseq(A, B) value(A) <= value(B)
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

int main() {
    int arr[] = {34, 3, 43, 5, 9, 7, 11, 45, 99};
    int k = 3;
    quick_select(arr, 0, 8, k);

    for(int i = 0; i < k; i++)
        printf("%d\n", arr[i]);
}
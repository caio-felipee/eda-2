#include <stdlib.h>

#define higher(A, B) A > B
typedef int Item;

void insertion_sort(Item *array, int l, int r) {
    for(int i = l + 1; i <= r; i++) {
        Item key = array[i];
        int j = i - 1;

        while(j >= l && higher(array[j], key)) {
            array[j + 1] = array[j];
            j = j - 1;
        }

        array[j + 1] = key;
    }
}
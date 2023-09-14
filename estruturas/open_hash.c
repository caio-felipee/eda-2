#include <stdlib.h>
#include <stdbool.h>

#define M 31879
#define STEP 10
#define NULLItem -1
#define KEY(A) A % M

typedef int Item;

bool insert(Item *hash, Item value) {
    if(search(hash, value))
        return;

    int key = KEY(value);

    for(int i = key; i <= key + STEP; i++) {
        if(hash[i] == NULLItem) {
            hash[i] = value;
            return true;
        }
    }

    return false;
}

bool search(Item *hash, Item value) {
    int key = KEY(value);

    for(int i = key; i <= key + STEP; i++) {
        if(hash[i] == value)
            return true;
    }

    return false;
}

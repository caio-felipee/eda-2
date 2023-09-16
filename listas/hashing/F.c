// Hash It!

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SMAX 20
#define MAX 101
#define HASH(key, j) ((key % MAX) + (j * j) + (23 * j)) % MAX
#define ST 4

char hash[101][16] = {0};

bool is_equal(char *str1, char *str2) {
    int i;
    for(i = 0; str1[i] != 0 && str2[i] != 0; i++) {
        if(str1[i] != str2[i])
            return false;
    }

    return str1[i] == str2[i];
}

int h(char *key) {
    int ans = 0;

    for(int i = 0; key[i] != '\0'; i++) {
        ans += ((int)key[i] * (i + 1));
    }

    return ans * 19;
}

int add(char *key) {
    for(int i = 0; i < MAX; i++) {
        if(hash[i][0] && is_equal(key, hash[i])) {
            return 0;
        }
    }

    int hs = h(key);
    for(int i = 0; i <= 19; i++) {
        int k = HASH(hs, i);
        if(!hash[k][0]) {
            strcpy(hash[k], key);
            return 1;
        }
    }

    return 0;
}

int del(char *key) {
    for(int i = 0; i < MAX; i++) {
        if(hash[i][0] && is_equal(key, hash[i])) {
            hash[i][0] = 0;
            return 1;
        }
    }

    return 0;
}

int main() {
    int t, n;
    scanf("%d", &t);

    while(t--) {
        int size = 0;
        scanf("%d", &n);

        while(n--) {
            char str[20];
            scanf(" %s", str);

            if(str[0] == 'A') { // add!
                size += add(str + 4);
            }
            else { // remove!
                size -= del(str + 4);
            }
        }

        printf("%d\n", size);
        for(int i = 0; i < MAX; i++) {
            if(hash[i][0]) {
                printf("%d:%s\n", i, hash[i]);
                hash[i][0] = 0;
            }
        }
    }
}
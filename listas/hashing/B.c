#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

int main() {
    char str[MAX];

    while(scanf(" %s", str) != EOF) {
        int *hash = calloc(129, sizeof(int));
        int freq = MAX;

        for(int i = 0; str[i] != '\0'; i++) {
            hash[str[i]]++;
            freq = freq < hash[str[i]] ? freq : hash[str[i]];
        }

        int next;
        for(int i = 33; i < 128; i++) {
            next = MAX;

            for(int j = 33; j < 128; j++) {
                if(hash[j] == freq && hash[j] != MAX) {
                    printf("%d %d\n", j, hash[j]);
                    hash[j] = MAX;
                }

                if(hash[j] > freq && next > hash[j])
                    next = hash[j];
            }

            freq = next;
        }

        printf("\n");
        free(hash);
    }

    return 0;
}
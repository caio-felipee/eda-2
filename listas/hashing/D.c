// Notas curiosas

#include <stdio.h>

#define MAX 1001

int main() {
    int hash[MAX] = {0}, n, ans = 0, t;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &t);
        if(++hash[t] > hash[ans] || (hash[t] == hash[ans] && t > ans))
            ans = t;
    }

    printf("%d\n", ans);
    return 0;
}
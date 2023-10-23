// Desfile dos Patos

#include <stdio.h>
#include <stdlib.h>

#define MAX 10e6 + 1

int main() {
    int n;

    while(scanf("%d", &n) && n) {
        int *vs = calloc(MAX, sizeof(int));
        int ans = 0, t;

        for(int i = 0; i < n; i++) {
            scanf("%d", &t);

            if(vs[ans] < ++vs[t])
                ans = t;
        }

        printf("%d\n", ans);
        free(vs);
    }

    return 0;
}

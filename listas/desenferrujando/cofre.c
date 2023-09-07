#include <stdio.h>

int main() {
    int n, jt, zt, t = 1;
    while(scanf(" %d", &n) && n > 0) {
        int z = 0, j = 0;
        printf("Teste %d\n", t++);

        for(int i = 0; i < n; i++) {
            scanf(" %d %d", &jt, &zt);
            j += jt;
            z += zt;
            printf("%d\n", j - z);
        }
        printf("\n");
    }
}
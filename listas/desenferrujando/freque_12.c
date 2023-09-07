#include <stdio.h>

char st[(int)1e6 + 1] = {(char)0};

int main() {
    int n, tmp, ans = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf(" %d", &tmp);
        if(!st[tmp]++)
            ans++;
    }

    printf("%d\n", ans);
}
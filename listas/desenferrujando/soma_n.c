#include <stdio.h>

int main() {
    int n, tmp, ans = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf(" %d", &tmp);
        ans += tmp;
    }

    printf("%d\n", ans);
    return 0;
}
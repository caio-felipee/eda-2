#include <stdio.h>

int main() {
    int ans = 0, tmp;

    while(scanf(" %d", &tmp) == 1)
        ans++;
    
    printf("%d\n", ans);
}
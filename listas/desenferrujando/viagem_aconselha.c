#include <stdio.h>

int MAX = 1e7+1;

int main() {
    int day = 1, n, id, star;

    while(scanf(" %d", &n) == 1) {
        int best = MAX, stars = 0;

        for(int i = 0; i < n; i++) {
            scanf(" %d %d", &id, &star);

            if(star > stars || (star == stars && best > id)) {
                best = id;
                stars = star;
            }
        }
        
        printf("Dia %d\n", day++);
        printf("%d\n\n", best);
    }
}
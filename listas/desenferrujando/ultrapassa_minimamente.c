#include <stdio.h>

void solve(int *value, int max) {
    int v = 0;
    while(*value != 0) {
        v += *value;
        value++;

        if(v > max) {
            solve(value, max);
            printf("%d\n", *(value - 1));
            break;
        }
    }

    return;
}

int main() {
    int values[100000], i = 0;
    while(scanf(" %d", &values[i]) && values[i] != 0)
        i++;
    
    int max;
    scanf(" %d", &max);
    solve(values, max);
}
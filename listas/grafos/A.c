// Eu vou estar lá!

#include <stdio.h>
#include <stdbool.h>

int graph[2002][2002];
bool visited[2002] = {false};

int main() {
    int n, m, j;
    scanf("%d %d %d", &n, &m, &j);

    int a, t;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a);

        while(a--) {
            scanf("%d", &t);

            graph[i][t] = 1;
        }
    }

    for(int i = 0; i < m; i++) {
        scanf("%d", &t);
        
        visited[t] = true;
        for(int i = 0; i <= 2000; i++) {
            if(graph[t][i])
                visited[i] = true;
        }
    }

    for(int i = 0; i < j; i++) {
        scanf("%d", &t);
        printf("%s\n", visited[t] ? "Eu vou estar la" : "Nao vou estar la");
    }

    return 0;
}
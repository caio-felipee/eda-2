// Estradas asfaltadas - Perguntando conexões

#include <stdio.h>
#define MAX 2002
#define oo ((int)1e5 + 9)
#define comp(A, B) A <= B

int dist[MAX][MAX];
int pred[MAX][MAX];

void floyd_warshall(int N, int index) {
    for(int i = index; comp(i, N); i++) {
        dist[i][i] = 0;
        pred[i][i] = i;
    }

    for(int k = index; comp(k, N); k++) {
        for(int i = index; comp(i, N); i++) {
            if(dist[i][k] == oo) continue;
            
            for(int j = index; comp(j, N); j++) {
                if(dist[i][k] < oo && dist[k][j] < oo && dist[i][j] == oo) {
                    dist[i][j] = 1;
                    pred[i][j] = pred[k][j]; 
                }
            }
        }
    }
}

int main() {
    int n, v, w, d;
    scanf("%d", &n);

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dist[i][j] = oo;
        }
    }

    while(scanf("%d %d %d", &v, &w, &d) && d) {
        dist[v][w] = 1;

        if(d == 2)
            dist[w][v] = 1;
    }

    floyd_warshall(n, 0);


    int t, x;
    while(scanf("%d %d", &t, &x) != EOF) {
        if(dist[t][x] == dist[x][t]) 
            printf("%s\n", (dist[t][x] < oo ? "Ida e Volta" : "Impossibru"));
        else
            printf("%s\n", (dist[t][x] < oo ? "Apenas Ida" : "Apenas Volta"));
    }
}
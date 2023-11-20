#include <stdio.h>
#include <limits.h>

#define MAX 2002
#define comp(A, B) A <= B

const int oo = INT_MAX;
int dist1[MAX][MAX];
int dist2[MAX][MAX];

void floyd_warshall(int N, int index) {
    for(int i = index; comp(i, N); i++) {
        dist1[i][i] = 0;
        dist2[i][i] = 0;
    }

    for(int k = index; comp(k, N); k++) {
        for(int i = index; comp(i, N); i++) {
            if(dist1[i][k] == oo) continue;
                
            for(int j = index; comp(j, N); j++) {
                if(dist1[i][k] != oo && dist1[k][j] != oo && dist1[i][j] > dist1[i][k] + dist1[k][j]) {
                    // printf("d[%d][%d]: %d, d[%d][%d]: %d, d[%d][%d]: %d\n", i, j, dist1[i][j], i, k, dist1[i][k], k, j, dist1[k][j]);
                    dist1[i][j] = dist1[i][k] + dist1[k][j];
                }
            }
        }
    }

    // d[2][2] < 0. Entrou em um ciclo!
    for(int k = index; comp(k, N); k++) {
        for(int i = index; comp(i, N); i++) {
            for(int j = index; comp(j, N); j++) {
                // printf("d[%d][%d]: %d, d[%d][%d]: %d, d[%d][%d]: %d\n", i, j, dist1[i][j], k, j, dist1[k][j], j, j, dist1[j][j]);
                if(dist1[j][i] != oo && dist1[k][j] != oo && dist1[j][j] < 0) {
                    dist1[k][i] = oo;
                }
            }
        }
    }

    for(int k = index; comp(k, N); k++) {
        for(int i = index; comp(i, N); i++) {
            if(dist2[i][k] == oo) continue;
                
            for(int j = index; comp(j, N); j++) {
                if(dist2[i][k] < oo && dist2[k][j] < oo && dist2[i][j] > dist2[i][k] + dist2[k][j]) {
                    dist2[i][j] = dist2[i][k] + dist2[k][j];
                }
            }
        }
    }
}

int main() {
    int V, v, w, c, t;
    scanf("%d", &V);

    for(int i = 0; i <= V; i++) {
        for(int j = 0; j <= V; j++) {
            dist1[i][j] = oo;
            dist2[i][j] = oo;
        }
    }

    while(scanf("%d %d %d %d", &v, &w, &c, &t) && v != w) {
        dist1[v][w] = c;
        if(!t) {
            dist1[w][v] = c;
            dist2[v][w] = c;
            dist2[w][v] = c;
        }
    }

    floyd_warshall(V, 0);

    int o, x;
    while(scanf("%d %d", &o, &x) != EOF) {
        if(dist1[o][x] == oo || dist2[x][o] == oo)
            printf("Impossibru\n");
        else
            printf("%d %d\n", dist2[o][x], dist1[o][x]);
    }
}
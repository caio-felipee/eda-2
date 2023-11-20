#include <stdio.h>
#define MAX 2002
#define oo ((int)1e5 + 9)
#define comp(A, B) A <= B

int dist[MAX][MAX] = {oo};
int pred[MAX][MAX] = {oo};

void floyd_warshall(int N, int index) {
    for(int i = index; comp(i, N); i++) {
        dist[i][i] = 0;
        pred[i][i] = i;
    }

    for(int k = index; comp(k, N); k++) {
        for(int i = index; comp(i, N); i++) {
            if(dist[i][k] == oo) continue;
                
            for(int j = index; comp(j, N); j++) {
                if(dist[i][k] < oo && dist[k][j] < oo && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j]; 
                }
            }
        }
    }
}
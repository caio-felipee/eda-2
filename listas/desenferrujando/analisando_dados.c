#include <stdio.h>
#include <stdlib.h>

#define Item pair
#define less(A, B) A.amount < B.amount

typedef struct pair {
    int amount;
    int started;
    char letter;
} pair;

int min(int x, int y) { return (x<y)? x :y; }

void merge(Item *V, int l, int m, int r)
{
  Item *R=malloc(sizeof(Item)*(r-l+1));
  int i=l,j=m+1,k=0;

  while(i<=m && j<=r)
  {
    if(less(V[i],V[j]))
      R[k++]=V[i++];
    else
      R[k++]=V[j++];
  }

  while(i<=m)
      R[k++]=V[i++];
  while(j<=r)
      R[k++]=V[j++];


  k=0;
  for(i=l;i<=r;i++)
    V[i]=R[k++];
  free(R);
}

void mergesort(Item *arr, int n) {
    for(int curr_size = 1; curr_size < n; curr_size *= 2) {
        for(int left_start = 0; left_start < n - 1; left_start += 2*curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            
            merge(arr, left_start, mid, right_end);
        }
    }
}

int main() {
    char tmp;
    int i = -1;
    int index = 0;
    pair *vs = malloc(sizeof(vs) * 112345);

    while(scanf("%c", &tmp) && tmp != '\n') {
        if(i < 0) {
            i = 0;
            vs[i].amount = 1;
            vs[i].letter = tmp;
            vs[i].started = index;
        }
        else if(vs[i].letter == tmp) {
            vs[i].amount++;
        }
        else {
            vs[++i].letter = tmp;
            vs[i].amount = 1;
            vs[i].started = index;
        }
        index++;
    }

    mergesort(vs, i + 1);

    for(int j = i; j >= 0; j--) {
        printf("%d %c %d\n", vs[j].amount, vs[j].letter, vs[j].started);
    }

    return 0;
}
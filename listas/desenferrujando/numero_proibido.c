#include <stdio.h>
#include <stdlib.h>

#define lesseq(A, B) A <= B
typedef int Item;

void merge(Item *V, int l, int m, int r)
{
  Item *R=malloc(sizeof(Item)*(r-l+1));
  int i=l,j=m+1,k=0;

  while(i<=m && j<=r)
  {
    if(lesseq(V[i],V[j]))
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

void mergesort(Item *V,int l, int r)
{
  if (l>= r) return;
  int meio=(l+r)/2;
  mergesort(V,l,meio);
  mergesort(V,meio+1,r);
  merge(V,l,meio,r);
}

int binary_search(Item *vs, int value, int l, int r) {
    while(r >= l) {
        int mid = l + (r - l) / 2;

        if(vs[mid] == value)
            return 1;
        
        if(vs[mid] > value)
            r = mid - 1;
        else
            l = mid + 1;
    }

    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    int vs[n];
    for(int i = 0; i < n; i++) {
        scanf(" %d", &vs[i]);
    }

    mergesort(vs, 0, n - 1);

    int tmp;
    while(scanf(" %d", &tmp) == 1)
        printf(binary_search(vs, tmp, 0, n - 1) ? "sim\n" : "nao\n");
    
    return 0;
}
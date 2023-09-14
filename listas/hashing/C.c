// Eleicao U.R.S.A.L    

#include <stdio.h>
#include <stdlib.h>

#define Item Candidate
#define KEY(A) A.votes
#define less(A, B) KEY(A) < KEY(B)
#define eq(A, B) A.digits <= B.digits && A.votes == B.votes

typedef struct Candidate {
    int votes;
    int digits;
} Candidate;

typedef struct Result {
    int r;
    struct Candidate *vs;
} Result;

Result left_shift(Candidate *vs, int max) {
    Candidate *values = calloc(max, sizeof(Candidate));
    int left = 0;

    for(int i = max; i >= 0; i--) {
        if(vs[i].votes > 0)
            values[left++] = vs[i];
    }

    free(vs);

    Result r = {left - 1, values};
    return r;
}

void merge(Item *vs, int l, int mid, int r)
{
    Item *v = malloc(sizeof(Item)*(r - l + 1));
    int i = l, j = mid + 1, k = 0;

    while(i <= mid && j <= r) 
    {
        if(less(vs[i], vs[j]) || eq(vs[i], vs[j]))
            v[k++] = vs[i++];
        else
            v[k++] = vs[j++];
    }

    while(i <= mid)
        v[k++] = vs[i++];
    
    while(j <= r)
        v[k++] = vs[j++];
    
    k = 0;
    for(i = l; i <= r; i++)
        vs[i] = v[k++];
    
    free(v);
}

void mergesort(Item *vs, int l, int r)
{
    if(l >= r)
        return;
    
    int mid = l + (r - l)/2;
    mergesort(vs, l, mid);
    mergesort(vs, mid + 1, r);
    merge(vs, l, mid, r);
}

int main() {
    int *presidentes = calloc(100, sizeof(int));
    Candidate *senadores = calloc(1000, sizeof(Candidate));
    Candidate *federal = calloc(10000, sizeof(Candidate));
    Candidate *estadual = calloc(100000, sizeof(Candidate));

    int S, F, E, valid = 0, invalid = 0, tmp;
    int president_votes = 0, best_president = 0;
    int ms = 0, mf = 0, me = 0;
    scanf("%d %d %d", &S, &F, &E);

    while(scanf("%d", &tmp) != EOF) {
        if(tmp < 0) {
            invalid++;
            continue;
        }

        valid++;

        if(tmp / 100 <= 0) {
            president_votes++;

            if(++presidentes[tmp] > presidentes[best_president])
                best_president = tmp;
        }
        else if(tmp / 1000 <= 0) {
            senadores[tmp].votes++;
            senadores[tmp].digits = tmp;

            ms = tmp > ms ? tmp : ms;
        }
        else if(tmp / 10000 <= 0) { 
            federal[tmp].votes++;
            federal[tmp].digits = tmp;
            mf = tmp > mf ? tmp : mf;
        }
        else {
            estadual[tmp].votes++;
            estadual[tmp].digits = tmp;
            me = tmp > me ? tmp : me;
        }
    }

    Result s = left_shift(senadores, ms);
    Result f = left_shift(federal, mf);
    Result e = left_shift(estadual, me);
    mergesort(s.vs, 0, s.r);
    mergesort(f.vs, 0, f.r);
    mergesort(e.vs, 0, e.r);

    printf("%d %d\n", valid, invalid);

    if((double)presidentes[best_president]/(double)president_votes >= 0.51) {
        printf("%d\n", best_president);
    }
    else {
        printf("Segundo Turno\n");
    }

    for(int i = s.r, j = 1; j <= S && i >= 0; i--, j++) {
        printf("%d%c", s.vs[i].digits, j < S ? ' ' : '\n');
    }

    for(int i = f.r, j = 1; j <= F && i >= 0; i--, j++) {
        printf("%d%c", f.vs[i].digits, j < F ? ' ' : '\n');
    }

    for(int i = e.r, j = 1; j <= E && i >= 0; i--, j++) {
        printf("%d%c", e.vs[i].digits, j < E ? ' ' : '\n');
    }
}
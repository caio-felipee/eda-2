#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX ((int)1e6 + 19)
#define RAND 493
#define MUL 23
#define SMAX 101

typedef struct User {
    bool used;
    int id;
    char *fn;
    char *ln;
    char *bd;
    char *tel;
} User;

typedef struct List {
    int id;
    struct List *next;
} List;

typedef struct Queries {
    struct List *fn;
    struct List *ln;
    struct List *bd;
    struct List *tel;
} Queries;

/*
* Criar um Hash utilizando os IDs como chave
* Para cada informação que possuo, apontar um Hash para o identificador
* Ações: add, query, info, del 
*/

int h(char *key) {
    int hs = 1;
    int a = RAND;

    for(int i = 0; key[i] != 0; i++) {
        a = (((a * key[i]) % MAX) - a) - (i * MUL);
        hs = ((hs * a) % MAX);

        if(hs < 0)
            hs = (hs + MAX) % MAX;
    }

    return hs;
}

void make_query(int id, char *key, List *query) {
    id %= MAX;
    int k = h(key);
    
    List *vs = malloc(sizeof(List));
    vs->next = query[k].next;
    vs->id = id;
    query[k].next = vs;
}

bool add(int id, char *first_name, char *last_name, char *birth, char *phone, User *hash, Queries queries) {
    int mid = (id % MAX);
    if(hash[mid].used)
        return false;
    
    // printf("created %d %d %d %s %s\n", mid, id, MAX, first_name, last_name);
    hash[mid].used = true;
    char *fn = malloc(SMAX);
    char *ln = malloc(SMAX);
    char *bd = malloc(SMAX);
    char *ph = malloc(SMAX);
    strcpy(fn, first_name);
    strcpy(ln, last_name);
    strcpy(bd, birth);
    strcpy(ph, phone);

    hash[mid].fn = fn;
    hash[mid].ln = ln;
    hash[mid].bd = bd;
    hash[mid].tel = ph;
    hash[mid].id = id;

    make_query(id, fn, queries.fn);    
    make_query(id, ln, queries.ln);    
    make_query(id, bd, queries.bd);    
    make_query(id, ph, queries.tel);    

    return true;
}

bool del(int id, User *hash) {
    id %= MAX;
    if(!hash[id].used)
        return false;
    
    hash[id].used = false;
    free(hash[id].fn);
    free(hash[id].ln);
    free(hash[id].bd);
    free(hash[id].tel);

    return true;
}

User info(int id, User *hash) {
    id %= MAX;
    return hash[id];
}

bool is_equal(char *str1, char *str2) {
    if(str1[0] == 0 || str2[0] == 0)
        return true;
    
    int i;
    for(i = 0; str1[i] != 0 && str2[i] != 0; i++) {
        if(str1[i] != str2[i])
            return false;
    }

    return str1[i] == str2[i];
}

void query(char *fn, char *ln, char *bd, char *ph, User *hash, Queries queries) {
    List q = (List){-1, NULL};

    if(fn[0] != 0) {
        q = queries.fn[h(fn)];
    }
    else if(ln[0] != 0) {
        q = queries.ln[h(ln)];
    }
    else if(bd[0] != 0) {
        q = queries.bd[h(bd)];
    }
    else {
        q = queries.tel[h(ph)];
    }

    int vt[SMAX], qtd = 0;
    while(q.next != NULL) {
        q = *q.next;
        User user = hash[q.id];
        // printf("%d oi\n", q.id);

        if(user.used && is_equal(fn, user.fn) && is_equal(ln, user.ln) && is_equal(bd, user.bd) && is_equal(ph, user.tel)) {
            vt[qtd++] = user.id;
        }
    }

    for(int i = 0; i < qtd; i++) {
        for(int j = 0; j < qtd; j++) {
            if(i != j && vt[i] < vt[j]) {
                int t = vt[j];
                vt[j] = vt[i];
                vt[i] = t;
            }
        }
    }

    for(int i = 0; i < qtd; i++) {
        printf("%d", vt[i]);
        
        if(i < qtd - 1)
            printf(" ");
    }
    
    printf("\n");
}

int main() {
    User *hash = calloc(MAX, sizeof(User));
    List *fn = calloc(MAX, sizeof(List));
    List *ln = calloc(MAX, sizeof(List));
    List *bd = calloc(MAX, sizeof(List));
    List *tel = calloc(MAX, sizeof(List));

    Queries queries = (Queries){fn, ln, bd, tel};
    char act[6];

    while(scanf(" %s", act) != EOF) {
        if(act[0] == 'a') {
            char first_name[SMAX], last_name[SMAX], birth[SMAX], phone[SMAX];
            int id;
            scanf("%d %s %s %s %s", &id, first_name, last_name, birth, phone);

            if(!add(id, first_name, last_name, birth, phone, hash, queries))
                printf("ID %d ja cadastrado.\n", id);
        }
        else if(act[0] == 'd') {
            int id;
            scanf("%d", &id);

            if(!del(id, hash))
                printf("ID %d nao existente.\n", id);
        }
        else if(act[0] == 'i') {
            int id;
            scanf("%d", &id);

            User user = info(id, hash);
            if(!user.used)
                printf("ID %d nao existente.\n", id);
            else
                printf("%s %s %s %s\n", user.fn, user.ln, user.bd, user.tel);
        }
        else {
            char str[SMAX], t;
            char f[SMAX], l[SMAX], b[SMAX], p[SMAX];
            f[0] = 0;
            l[0] = 0;
            b[0] = 0;
            p[0] = 0;

            scanf("%c", &t);
            while(scanf("%s%c", str, &t)) {
                if(str[0] == 'f') {
                    strcpy(f, str + 3);
                }
                if(str[0] == 'l') {
                    strcpy(l, str + 3);
                }
                if(str[0] == 'b') {
                    strcpy(b, str + 3);
                }
                if(str[0] == 'p') {
                    strcpy(p, str + 3);
                }
                if(t == '\n')
                    break;
            }
            query(f, l, b, p, hash, queries);
        }
    }
}
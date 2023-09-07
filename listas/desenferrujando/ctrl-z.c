#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Item;

typedef struct Linked_list {
    Item *item;
    struct Linked_list *next;
} Linked_list;

typedef struct {
    struct Linked_list *top;
    int size;
} Stack;

Stack *createStack() {
    Stack *s = malloc(sizeof(Stack));

    s->top = NULL;
    s->size = 0;

    return s;
}

Item *top(Stack *s) {
    if(!s->size)
        return NULL;

    return s->top->item;
}

void pop(Stack *s) {
    if(!s->size)
        return;
    
    Linked_list *aux = s->top;
    
    s->top = s->top->next;
    s->size--;

    free(aux->item);
    free(aux);
}

void push(Stack *s, Item *item) {
    Linked_list *aux = malloc(sizeof(Linked_list));

    aux->item = item;
    aux->next = s->top;

    s->top = aux;
    s->size++;
}

/*
* Stack reaproveitada, feita pelo próprio autor.
* https://github.com/caio-felipee/trabalho-eda/blob/main/data_structures/dynamic_stack.c
*/
int main() {
    Stack *stack = createStack();

    char act[10], tsh;  
    while(scanf(" %s%c", act, &tsh) != EOF) {
        if(strcmp(act, "desfazer") == 0) {
            if(stack->top == NULL) {
                printf("NULL\n");
            }
            else {
                printf("%s\n", stack->top->item);
                pop(stack);
            }
        }
        else {
            Item *tmp = malloc(sizeof(Item)*101);
            int i = 0;
            while(scanf("%c", &tmp[i]) && tmp[i++] != '\n');
            tmp[i - 1] = 0;
            push(stack, tmp);
        }
    }
}
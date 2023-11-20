#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define value_rb(A) A
#define less_rb(A, B) value_rb(A) < value_rb(B)

typedef int Item;

typedef struct node {
    struct node *left, *right;
    bool red;
    Item value;
    int rep;
} node;

node *new_node(Item item, bool red) {
    node *n = malloc(sizeof(node));
    n->red = red;
    n->value = item;
    n->rep = 1;
    n->right = NULL;
    n->left = NULL;

    return n;
}

bool is_red(node *n) {
    return n != NULL ? n->red : false;
}

node *rotate_left(node *n) {
    node *t = n->right;
    n->right = t->left;
    t->left = n;
    t->red = n->red;
    n->red = true;

    return t;
}

node *rotate_right(node *n) {
    node *t = n->left;
    n->left = t->right;
    t->right = n;
    t->red = n->red;
    n->red = true;

    return t;
}

void flip_colors(node *n) {
    n->red = true;
    n->left->red = false;
    n->right->left = false;
}

node *insert_rb(node *n, Item value) {
    if(n == NULL) return new_node(value, true);
    if(less_rb(value, n->value)) n->left = insert_rb(n->left, value);
    else if(less_rb(n->value, value)) n->right = insert_rb(n->right, value);
    else n->rep++;

    if(!is_red(n->left) && is_red(n->right)) n = rotate_left(n);
    if(is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);
    if(is_red(n->left) && is_red(n->right)) flip_colors(n);

    return n;
}

node *find_rb(node *n, Item value) {
    if(n == NULL)
        return NULL;

    if(value_rb(n->value) > value_rb(value))
        find_rb(n->left, value);
    else if(value_rb(n->value) < value_rb(value))
        find_rb(n->right, value);
    else
        return n;
}

void inorder_rb(node *n) {
    if(n == NULL)
        return;
    
    inorder_rb(n->left);
    printf("%d\n", value_rb(n->value));
    inorder_rb(n->right);
}

int main() {
    node *rb = NULL;

    rb = insert_rb(rb, 100);
    rb = insert_rb(rb, 150);
    rb = insert_rb(rb, 100);
    rb = insert_rb(rb, 50);
    rb = insert_rb(rb, 10);
    rb = insert_rb(rb, 15);
    inorder_rb(rb);
}
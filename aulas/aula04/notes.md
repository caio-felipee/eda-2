## LLD Red-Black

### Lower Bound
```c
node *floor(node *h, Item key) 
{
    if(h == NULL) return NULL;

    if(less(key, h->item))
        return floor(h->left, key);
    
    else if(key == h->item)
        return h;
    
    node *aux = floor(h->right, key);

    return aux != NULL ? aux : h;
}
```
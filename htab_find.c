// htab_find.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"
#include "htab_struct.h"

htab_pair_t * htab_find(const htab_t * t, htab_key_t key)
{
    struct htab_item *item= t->arr[htab_hash_function(key)%t->arr_size];
    while(item!=NULL)
    {
        if(strcmp(item->pair.key,key)==0)
        {
            return &item->pair;
        }
        item=item->next;
    }
    return NULL;
}
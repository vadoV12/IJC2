// htab_erase.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"
#include "htab_struct.h"

bool htab_erase(htab_t * t, htab_key_t key)
{
    struct htab_item *item=t->arr[htab_hash_function(key)%t->arr_size];
    struct htab_item *prev = NULL;
    while(item!=NULL)
    {
        if(strcmp(item->pair.key,key)==0)
        {
            if(prev==NULL)
            {
                t->arr[htab_hash_function(key)%t->arr_size] = item->next;
            }
            else
            {
                prev->next=item->next;
            }
            free((char *)item->pair.key);
            free(item);
            t->size--;
            return true;
        }
        prev=item;
        item=item->next;
    }
    return false;
}
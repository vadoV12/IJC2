// htab_free.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"
#include "htab_struct.h"

void htab_clear(htab_t * t)
{
    for(size_t i=0;i<t->arr_size;i++)
    {
        struct htab_item *item=t->arr[i];
        while(item!=NULL)
        {
            struct htab_item *tmp=item->next;
            free((char *)item->pair.key);
            free(item);
            t->size--;
            item=tmp;
        }
    t->arr[i]=NULL;
    }
}

void htab_free(htab_t * t)
{
    htab_clear(t);
    for(size_t i=0;i<t->arr_size;i++)
    {
        free(t->arr[i]);
    }
    free(t);
}

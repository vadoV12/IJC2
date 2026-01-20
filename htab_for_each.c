// htab_for_each.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"
#include "htab_struct.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    for (size_t i=0;i<t->arr_size;i++) 
    {
        struct htab_item *item=t->arr[i];
        while(item!=NULL) 
        {
            f(&item->pair); 
            item=item->next;
        }
    }
}
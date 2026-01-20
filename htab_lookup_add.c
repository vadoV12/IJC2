// htab_lookup_add.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"
#include "htab_struct.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)
{
    size_t index=htab_hash_function(key)%t->arr_size;
    struct htab_item *item=t->arr[index];
    while(item!=NULL)
    {
        if(strcmp(item->pair.key,key)==0)
        {
            item->pair.value=item->pair.value+1;
            return &item->pair;
        }
        item=item->next;
    }
    struct htab_item *newItem=NULL;
    newItem=malloc(sizeof(struct htab_item));
    if(newItem==NULL)
    {
        fprintf(stderr,"Allocation failed\n");
        return NULL;
    }
    size_t length=strlen(key)+1; 
    newItem->pair.key=malloc(length);
    if(newItem->pair.key==NULL)
    {
        fprintf(stderr,"Allocation failed\n");
        free(newItem);
        return NULL; 
    }
    memcpy((char *)newItem->pair.key,key,length); 
    newItem->pair.value=1;
    newItem->next=t->arr[index];
    t->arr[index]=newItem;
    t->size=t->size+1;
    return &newItem->pair;
}
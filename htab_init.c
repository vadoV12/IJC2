// htab_init.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"
#include "htab_struct.h"

htab_t *htab_init(size_t n)
{
    htab_t *tabulka=NULL;
    size_t size=((n*12)+9)/10; //zoberem rezervu 20% z predom odhadovanej velkosti n a zaokruhlujem nahor
    tabulka=malloc(sizeof(htab_t)+ sizeof(struct htab_item*)*size);
    if(tabulka==NULL)
    {
        fprintf(stderr,"Inicialization failed\n");
        return NULL;
    }
    tabulka->size=0;
    tabulka->arr_size=size;
    for(size_t i=0;i<tabulka->arr_size;i++) 
    {
        tabulka->arr[i] = NULL;
    }
    return tabulka;
}
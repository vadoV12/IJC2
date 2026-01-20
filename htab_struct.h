// htab_struct.h
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"

#ifndef _HTAB_S
#define _HTAB_S

struct htab
{
    size_t size;       
    size_t arr_size;    
    struct htab_item *arr[]; 
};

struct htab_item 
{
    htab_pair_t pair;        
    struct htab_item *next;  
};

#endif
 
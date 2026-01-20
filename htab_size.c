// htab_size.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT

#include "htab.h"
#include "htab_struct.h"

size_t htab_size(const htab_t * t)
{
    return t->size;
}

size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}
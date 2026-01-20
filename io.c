// io.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <ctype.h>

#include "io.h"

int read_word(unsigned max, char s[max], FILE * f)
{
    static int warning=0;
    int c=0;

    while(isspace((c=fgetc(f))) && c!=EOF);      

    if(c==EOF)
    {
        return EOF;
    }

    int unsigned index=1;
    while((c=fgetc(f))!=EOF)
    {
        if(index>=max-1)
        {
            s[index]='\0';
            if(warning==0)
            {
            fprintf(stderr,"Maximum chars in one line\n");
            warning=1;
            }
            while (!isspace((c=fgetc(f))) && c!=EOF);
            return index;
        }

        if(!isspace(c))
        {
            s[index]=c;
            index++;
        }

        if(isspace(c))
        {
            s[index]='\0';
            return index;   
        }
    }

    return index;
}
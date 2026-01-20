// maxwordcount.c
// Řešení IJC-DU2, příklad b) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <ctype.h>
#include "htab.h"

htab_pair_t **max_pairs;
size_t max_pairs_count = 0;
htab_value_t max_value = 0;
size_t capacity=0;

void find_max(htab_pair_t *data) 
{
    if(data->value>max_value) 
    {
        max_value=data->value;
        max_pairs_count=1;
        capacity=10; 
        free(max_pairs); 
        max_pairs=malloc(sizeof(htab_pair_t *)*capacity);
        if(max_pairs==NULL) 
        {
            fprintf(stderr,"Allocation failed\n");
            exit(1);
        }
        max_pairs[0]=data;
    } 
    else if(data->value==max_value) 
    {
        if (max_pairs_count>=capacity) 
        {
            capacity=capacity*2;
            htab_pair_t **temp=realloc(max_pairs,sizeof(htab_pair_t *)*capacity);
            if(temp==NULL) 
            {
                fprintf(stderr,"Allocation failde\n");
                free(max_pairs);
                exit(1);
            }
            max_pairs = temp;
        }
        max_pairs[max_pairs_count++] = data;
    }
}

void read_word(unsigned max, char s[max], FILE * f,htab_t *t)
{
    static int warning=0;
    int c=0;

    if(c==EOF)
    {
        exit(0);
    }

    int unsigned index=0;
    while((c=fgetc(f))!=EOF)
    {
        if(index>=max-1)
        {
            s[index] = '\0';
            if(warning==0)
            {
                fprintf(stderr,"Maximum chars in one line\n");
                warning=1;
            }
            while (!isspace((c=fgetc(f))) && c!=EOF);
            htab_lookup_add(t,s);
            memset(s,'\0',max);
            index=0;
            continue;
        }

        if(!isspace(c))
        {
            s[index]=c;
            index++;
        }

        if(isspace(c))
        {
            s[index]='\0';
            if (index>0 && s[0]!='\0') 
            {
                s[index]='\0'; 
                htab_lookup_add(t, s);
            }
            memset(s,'\0',max);
            index=0;
            continue;
        }
    }
    if (index>0 && s[0]!='\0') 
    {
        s[index]='\0'; 
        htab_lookup_add(t, s);
    }
}

FILE *openingFile(int argc, char *argv[]) 
{
    FILE *F=stdin;
    if(argc>1)
    {
        F=fopen(argv[1],"r");
    }
    if (F==NULL) 
    {
        fprintf(stderr,"File cannot be opened\n");
        return NULL;
    }
    return F;
}

int main(int argc,char *argv[]) 
{
    FILE *F=NULL;
    if((F=openingFile(argc,argv))==NULL)
    {
        if(F!=NULL)
        {
            fclose(F);
        }
        return 1;
    }
    char buff[256]; 
    htab_t *tabulka=htab_init(50000);
    if(tabulka==NULL)
    {
        return 1;
    }
    read_word(256,buff,F,tabulka);
    htab_for_each(tabulka,find_max);    
    if(max_pairs_count>0) 
    {
        for (size_t i=0;i<max_pairs_count;i++) 
        {
            printf("%s\t%d\n",max_pairs[i]->key,max_pairs[i]->value);
        }
    }
    htab_free(tabulka);
    fclose(F);
    free(max_pairs);
}
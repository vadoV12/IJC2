// tail.c
// Řešení IJC-DU2, příklad a) 5.4.2025
// Autor: Andrej Vadovsky,xvadova00,FIT
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <ctype.h>

#define FOLDER_MAX_WORDS 4097

typedef struct
{
    char** line;
    unsigned int head,tail,size,oversize;
}Circular_buffer;

void cbuf_free(Circular_buffer *cb)
{
    for (unsigned int i=0;i<cb->size;i++) 
    {
        free(cb->line[i]); 
    }
    
    free(cb->line); 
    free(cb);
} 

void cbuf_get(Circular_buffer *cb)
{
    unsigned int count=0;
    if(cb->oversize==1)
    {
        count=cb->head;
    }
    else
    {
        count=cb->tail;
    }
    do
    {
        printf("%s",cb->line[count]);
        count=(count+1)%cb->size;
    }while(count!=cb->head);
}

void cbuf_put(Circular_buffer *cb,char *line)
{
    if((cb->head+1)%cb->size==cb->tail) 
    {
        cb->tail=(cb->tail+1)%cb->size;
        cb->oversize=1; 
    }

    if (cb->line[cb->head] != NULL) 
    {
        free(cb->line[cb->head]);
    }

    cb->line[cb->head]=line;
    cb->head=(cb->head+1)%cb->size;
}

Circular_buffer *cbuf_create(unsigned n)
{
    Circular_buffer *cb = (Circular_buffer *)malloc(sizeof(Circular_buffer));
    if(cb==NULL)
    {
        fprintf(stderr,"Allocation failed\n");
        return NULL;
    }
    cb->line=calloc(n,sizeof(char *));
    if(cb->line==NULL)
    {
        free(cb);
        fprintf(stderr,"Allocation failed\n");
        return NULL;
    }
    cb->head=0;
    cb->tail=0;
    cb->size=n;
    return cb;
}

FILE *openingFile(int argc, char *argv[], unsigned *n) 
{
    FILE *F=stdin;
    for(int i=1;i<argc;i++) 
    {
        if(strcmp(argv[i],"-n")==0) 
        {
            if (i+1>=argc) 
            {
                fprintf(stderr,"Missing number after -n\n");
                return NULL;
            }

            for (size_t t=0;t<strlen(argv[i+1]);t++) 
            {
                if (!isdigit(argv[i+1][t])) 
                {
                    fprintf(stderr, "Char after -n\n");
                    return NULL;
                }
            }

            char *endptr;
            *n=strtoul(argv[i+1],&endptr,10);
            if(*n==0) 
            {
                exit(0);  
            }
            i++;  
        } 
        else 
        {
            F=fopen(argv[i],"r");
            if (F==NULL) 
            {
                fprintf(stderr,"Cannot open file\n");
                return NULL;
            }
        }
    }
    return F;
}

int main(int argc,char *argv[])
{
    FILE *F=NULL;
    unsigned n=0;
    if((F=openingFile(argc,argv,&n))==NULL)
    {
        if(F!=NULL)
        {
            fclose(F);
        }
        return 1;
    } 
    if(n==0)
    {
        n=10;
    }
    Circular_buffer* cb=NULL;
    if((cb=cbuf_create(n))==NULL)
    {
        fprintf(stderr,"Allocation failed\n");
        fclose(F);
        return 1;
    }
    char row[FOLDER_MAX_WORDS];
    if(fgetc(F)==EOF)
    {
        fclose(F);
        cbuf_free(cb);
        return 0;
    }
    rewind(F);
    while(fgets(row,sizeof(row),F)!=NULL) 
    {
        if(row[strlen(row)-1]!='\n' && !feof(F)) 
        {
            static int warned = 0; 
            if(!warned) 
            {
                fprintf(stderr,"Over 4095 chars in one line\n");
                warned = 1;
            }
            int c;
            while ((c=fgetc(F))!='\n' && c!=EOF);
            if(c!=EOF)
            {
                row[FOLDER_MAX_WORDS-2]='\n';
                row[FOLDER_MAX_WORDS-1]='\0';
            }
            else
            {
                row[FOLDER_MAX_WORDS-2]='\0';   
            }
        }
    
        char *line =(char *)malloc(strlen(row)+1);
        if(line==NULL)
            {
                fprintf(stderr,"Allocation failed\n");
                fclose(F);
                cbuf_free(cb);
                return 1;
            }
        strcpy(line,row);
        cbuf_put(cb,line);
    }

    cbuf_get(cb);
    fclose(F);
    cbuf_free(cb);
    return 0;
}
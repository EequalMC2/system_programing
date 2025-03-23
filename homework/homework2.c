#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true    1
#define false   0

char **split( char *pos, const char *delim)
{

    char *beg;
    char** dynstr = NULL;
    size_t size = 5;

    //dinamik bellek elde etme
    if( (dynstr = (char**)malloc(size * sizeof(char*))) == NULL){

        fputs("malloc  yer ayıramadı", stderr);
        exit(EXIT_FAILURE);
    }



    for(size_t i = 0; true; ++i){

    while(*pos != '\0' && strchr(delim, *pos) != NULL)
        ++pos;

    if(*pos == '\0')
        break;
    beg = pos;
    while(*pos != '\0' && strchr(delim, *pos) == NULL)
      ++pos;
    if(*pos)
        *pos++ = '\0';

    if(i >= size){
        if((dynstr = (char**) realloc(dynstr,sizeof(char*)*size*2)) == NULL){
            fputs("realloc  yer ayıramadı", stderr);
            exit(EXIT_FAILURE);
        }
        size *= 2;
    }


    if(*pos == '\0') {
        dynstr[i] = beg;
        dynstr[++i]  = NULL;
        break;
        }
    dynstr[i] = beg;
    }
    return dynstr;
}

int main(void)
{


    char  names[] = ",,,,,,ali, veli, selami,,,,,, hakan, tuncay, salih, fatma, nur,,,,,,";
    char  **ppstr;
    ppstr = split(names, ", ");
    for  (int i = 0; ppstr[i] != NULL; ++i)
            puts(ppstr[i]);
    return 0;
}









#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true    1
#define false   0

char **split( const char *str, const char *delim)
{
    char * cpy_str;
    char *beg;
    char** dyn_str = NULL;
    size_t size = 5;

    //char** dynstr icin dinamik bellek elde etme
    if( (dyn_str = (char**)malloc(size * sizeof(char*))) == NULL){

        fputs("malloc  yer ayıramadı", stderr);
        exit(EXIT_FAILURE);
    }

    //char* dynstr icin dinamik bellek elde etme
    if((cpy_str = (char*)malloc(strlen(str) + 1)) == NULL){
        fputs("malloc can not allocate...!",stderr);
        exit(EXIT_FAILURE);
    }

    // const char str dizisi dinamik char cpy_str dizisine aktarilir
    strcpy(cpy_str,str);

    //for dongusunun icinde cpy_str pars edilir ve degerler dyn_str dizisine aktarılır.
    for(size_t i = 0; true; ++i){

            while(*cpy_str != '\0' && strchr(delim, *cpy_str) != NULL)
                ++cpy_str;

            if(*cpy_str == '\0')
                break;
            beg = cpy_str;
            while(*cpy_str != '\0' && strchr(delim, *cpy_str) == NULL)
                ++cpy_str;
            if(*cpy_str)
                *cpy_str++ = '\0';


            // dyn_str realloc ile bellegi genisletilir.
            if(i >= size){
                if((dyn_str = (char**) realloc(dyn_str,sizeof(char*)*size*2)) == NULL){
                    fputs("realloc  can not allocate", stderr);
                    exit(EXIT_FAILURE);
                }
                size *= 2;
            }

            //char** dyn_str dizisinin her bir ogersi icin char* turunden bellek ayrıldı.
            if((dyn_str[i] = (char*)malloc(strlen(beg)+1)) == NULL){
                fputs("realloc  can not allocate", stderr);
                exit(EXIT_FAILURE);
            }


            //cpy_str dizisinin son ogesi oldugundan
            if(*cpy_str == '\0') {
                strcpy(dyn_str[i], beg);
                // son NULL pointer icin yer ayrılıyor.
                if((dyn_str[++i] = (char*)malloc(sizeof(char*))) == NULL){
                    fputs("realloc  can not allocate", stderr);
                    exit(EXIT_FAILURE);
                }
                dyn_str[i] = NULL;
                break;
            }

            strcpy(dyn_str[i], beg);
     }

    return dyn_str;
}

int main(void)
{
    char  **ppstr;
    ppstr = split(",,,,Hello,, form ,,,,,the,, other,, side,,", ", ");
    for  (size_t i = 0; ppstr[i] != NULL; ++i)
            puts(ppstr[i]);

    for(size_t i = 0; ppstr[i] != NULL; ++i){
            free(ppstr[i]);
    }
    free(ppstr);
    return 0;
}





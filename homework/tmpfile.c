
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_LEN 4096



int main()
{
    FILE *f;
    int i, val;

    if((f = tmpfile()) == NULL){
        fprintf(stderr,"connot create temporary file...\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < 100; ++i)
        if(fwrite(&i,sizeof(int),1,f) != 1){
            fprintf(stderr,"cannot write file..!\n");
            exit(EXIT_FAILURE);
        }


    fseek(f, 0, SEEK_SET);

    while(fread(&val, sizeof(int), 1, f) == 1)
            fprintf(stdout,"%d",val);

    if(ferror(f)){
        fprintf(stdout,"connot read file!...\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");
    return 0;
}










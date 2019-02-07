#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, const char* argv[] )
{
    int result;
    int aflag = 0, bflag = 0, cflag = 0, dflag = 0;
    char *carg, *darg;
    

    opterr = 0;
    while((result = getopt(argc, argv, "abc:d:")) != -1)
    {
        switch(result){

        case 'a' :
            aflag = 1;
            break;

        case 'b' :
            bflag = 1;
            break;
        case 'c' :
            cflag = 1;
            carg = optarg;
            break;

        case 'd' :
            dflag = 1;
            darg = optarg;

        case '?' :
            if(optopt == 'c' || optopt == 'd')
                fprintf(stderr,"-%c option  given without an arguman\n",optopt);

            else
                fprintf(stderr, "invalid switch %c \n",optopt);
            break;
        }

        fprintf(stdout,"arguman without switch\n");
        for(int i = optind; i < argc; ++i)
            fputs(argv[i],stdout);

        if(aflag)
            puts("-a is given\n");

        if(bflag)
            puts("-b is given\n");

        if(cflag)
            printf("-c is given, its argument: %s \n", carg);

        if(dflag)
            printf("-d is given, its arguşment %s \n", darg);


        return 0;
        }

    }



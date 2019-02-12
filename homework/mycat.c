
//12.02.2019
//murat öner
//advence c and system programgim: homework 2 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#define  buffer_size  1023


int main(int argc, char *argv[])
{
    int ch;
    int  tflag = 0, hflag = 0, Hflag = 0, uflag = 0, lflag = 0;
    int  helpflag = 0, headflag = 0, tailflag = 0, versionflag = 0;
    unsigned char buf[buffer_size + 1];
    memset(buf, 0, buffer_size + 1);
    const char *headstr, *tailstr;

    static struct option long_opt[] = {
    {"help",no_argument, NULL, 0 },
    {"head",required_argument, NULL, 1 },
    {"tail",required_argument, NULL, 2  },
    {"version",no_argument  , NULL, 3  }, 	
    {      0,          0,   0, 0  },
    };


    while((ch = getopt_long(argc, argv, "Hhult", long_opt, NULL )) != -1){
	
	switch(ch) {
            case 't':
               tflag = 1;

            case 'H':
               Hflag = 1;
               break;

            case 'h':
               hflag = 1;
               break;
	    
	    case 'u':
	       uflag = 1;
	       break;
	    
            case 'l':
	       lflag = 1;
	       break;
	    
	    case  0 :
	       helpflag = 1;
	       break;
            
	    case  1 :
	       headflag = 1;
	       headstr  = optarg;
	       break;
	    
  	    case  2 :
	       tailflag = 1;
	       tailstr  = optarg;
	       break;		
           
	   case 3 :
	       versionflag = 1;
               break;
	   }
       }
	   
// protects for arguments and switch
	if( argc - optind != 1 && argc - optind != 0   ){
	 fprintf(stderr,"error!! birden fazla dosya girme\nfazladan girilen dosya ismi %s \n", argv[optind + 1] );
	 exit(1); 
	}
	if((argc - optind == 0) && !helpflag && !versionflag)
	{
	 fputs("dosya ismi girmediniz\n",stderr);
	exit(1);	
	}
//switch   --help
		if(helpflag){
	fputs("\nmycat <file>\n\n"
              "\n -t:\n"
              "    Bu seçenek dosyanın içeriğini text olarak gösterir.\n"
	      "    Default seçenektir.\n"
              "    (Yani hiçbir seçenek belirtilmemişse\n"
              "    default olarak dosya text biçimde görüntülenecektir.)\n"
	      "\n -h:\n"
              "    seçeneği alfabetik hex karakterlerini \n"
              "    küçk harf ile göstermektedir.\n"
              "\n -H:\n"
              "    -h seçeneği ile aynıdır. Ancak hex karakterleri\n"
              "    büyük harf ile gösterir.\n"
              "    -h ve -H seçenekleri beraber kullanılamamaktadır.\n"
              "\n --head <sayı>:\n"
              "    Bu seçenek dosyanın başındaki ilk n satırı görüntüler\n"
              "\n --tail <sayı>: \n"
              "    Bu seçenek dosyanın sonundaki son n satırı görüntüler.\n"
              "\n -u:\n    Dosyayı text olarak büyük harf görüntüler.\n"
              "    Bu seçenek -h ya da -H ile birlikte kullanılamamaktadır.\n"
              "\n -l:\n"   
              "    Dosyayı text olarak küçük harf görüntüler\n"
              "    Bu seçenek -h ya da -H ile birlikte kullanılamamaktadır.\n"
	      "\n --version:\n"
	      "    Argümansız uzun bir seçenetir.\n"
              "    Programın versiyon numarası ekrana basılacaktır.\n"
              ,stderr);	
	exit(0);	
	}
// long option --version	
	if(versionflag){
		fputs("mycat version 1.0\n",stdout);
		exit(0);	
	}
	
// file opened
	FILE *pf;
	unsigned int val;
	 
	  if((pf = fopen(argv[optind],"r")) == NULL){
	    fprintf(stderr,"file cannot opend\n");
	    fclose(pf);
	    exit(1);			
	  }

//option -t or default option
	if(tflag || (argc == 2) ){
	   
	  while((val = fread(buf, sizeof(char), buffer_size, pf)) > 0)
	  	fwrite( buf,sizeof(char) , val, stdout);
	  fclose(pf);
	  exit(0);	
	}

// option -H or option -h	
	if(!uflag &&( Hflag || hflag)){
	  int total;
	  while((val = fread(buf,sizeof(char),32,pf)) > 0){
		total += val;
		fprintf(stdout,Hflag ? "%07X  " : "%07x  ",total);		
		for(int i = 0; i < val; ++i)
		  fprintf(stdout,Hflag ? "%3X" : "%3x",buf[i]);	
		  fprintf(stdout,"\n");		
		
		}
	 fclose(pf);	 
	 exit(0);
		
	}	
// option -u	
	if(!(hflag || Hflag)  && uflag){
	char* lbuf;
	int counter = 0;
	while((val = fread(buf,sizeof(char), buffer_size, pf)) > 0){		
			lbuf = buf;
			counter = val;			
			while(counter--){
		     	*lbuf = toupper(*lbuf);
			++lbuf;
			}
		fwrite(buf, sizeof(char), val, stdout);
		}	
	fclose(pf);
	exit(0);	
	}
// option -l	
	if(!(hflag || Hflag)  && lflag){
	char* lbuf;
	int counter = 0;
	while((val = fread(buf,sizeof(char), buffer_size, pf)) > 0){		
			lbuf = buf;
			counter = val;			
			while(counter--){
		     	*lbuf = tolower(*lbuf);
			++lbuf;
			}
		fwrite(buf, sizeof(char), val, stdout);
		}	
	fclose(pf);
	exit(0);	
	}
// long option --head
	if(headflag){
	  	for(int i = 0; i < strlen(headstr); ++i){
	  		if(!isdigit(headstr[i])){
		  	fputs("eror --head argumen has to be digit",stderr);
			fclose(pf);		  	
			exit(1);		
		}
	  }
		int size_head = atoi(headstr);
	  	for(int i = 1; fgets(buf, buffer_size, pf) != NULL && i < size_head; ++i)
	    		fputs(buf, stdout);
	}	         	

// long option --tail	
	if(tailflag){
	  	for(int i = 0; i < strlen(tailstr); ++i){
	  		if(!isdigit(tailstr[i])){
		  	fputs("eror --tail argumen has to be digit\n",stderr);
			fclose(pf);		  	
			exit(1);		
		}
	  }
		int size_tail = atoi(tailstr);
		int size_line = 0;
		while(fgets(buf, buffer_size, pf) != NULL)	  	
			++size_line; 
		fseek(pf, 0, SEEK_SET); 		
		for(int i = 1; fgets(buf, buffer_size, pf) != NULL; ++i)
			if((size_line - i) < size_tail	)							
	    		fputs(buf, stdout);
	
		fclose(pf);
		exit(0);
	}	         	


		
	return 0;
   }




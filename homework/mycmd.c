#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CMD_LINE   		1024
#define MAX_CMD_PARAMS  	32
char g_cmdLine[MAX_CMD_LINE];
char *g_cmdParam[MAX_CMD_PARAMS];


typedef struct tagCMD{

   const char *cmdText;
   void(*proc)(void);

}CMD;

void parse_gmdLine(void);
void del_proc(void);
void copy_proc(void);
void clear_proc(void);

CMD g_cmds[] = {
   {"del", del_proc},
   {"copy",copy_proc},
   {"clear",clear_proc},	 
   {NULL,NULL}
   };



int main(void){
   int i;

   for (;;){
      fputs("CSD>",stdout);
      fgets(g_cmdLine,MAX_CMD_LINE,stdin);
      *strchr(g_cmdLine,10) = '\0';
      parse_gmdLine();
      for (i = 0; g_cmds[i].cmdText != NULL; ++i)
      if (!strcmp(g_cmdParam[0],g_cmds[i].cmdText)){
         g_cmds[i].proc();
         break;
         }
      if (g_cmds[i].cmdText == NULL)
         fputs("there is no command like this\n",stdout);
      }


   }



void parse_gmdLine()
{
   int counter = 0;
   char *str = NULL;

   for(str = strtok(g_cmdLine," \t"); str != NULL; str = strtok(NULL, " \t")){
      g_cmdParam[counter++] = str;
   }
}

void clear_proc(void)
{
  system("clear");
}
void del_proc(void)
{
   printf("del command\n");
}

void  copy_proc(void)
{
   printf("copy command\n");
}


;#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF_SIZE  10

void exit_sys(const char* str);

int main()
{

   int fd;
   char buf[BUF_SIZE + 1];
   ssize_t n;

   if((fd = open("/home/murat/Desktop/sirketadı.txt",O_RDONLY)) < 0)
       exit_sys("open");

   while((n = read(fd, buf, BUF_SIZE)) > 0){
      buf[n] = '\0';
      fputs(buf, stdout);
   }
   if(n == -1)
      exit_sys("read");
   close(fd);

   return 0;
}

void exit_sys(const char* str)
   {
      perror(str);
      exit(EXIT_FAILURE);

   }


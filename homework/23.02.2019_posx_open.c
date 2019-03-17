#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
// int open(const char *pathname, int flags, .....);
//first parameter is file's pathname

//secound parameter is :
//O_RDONLY
//O_WRONLY
//O_RDWR
//O_CREAT: Bu modda dosya yoksa yaratılır ve açılır, varsa olan dosya açılır.
//O_TRUNC: Bu modda dosya açılırken eğer dosya zaten varsa aynı zamanda sıfırlanmaktadır.
//O_APPEND: Bu modda dosyadan okuma yapılabilir. Ancak her yazma işlemi önce dosya göstericisinin dosyanın sonuna çekilmesiyle yapılmaktadır. Yani her write işlemi sona eklemeye yol açar
//O_EXCL: Bu modda yaratım sırasında dosya varsa open fonksiyonu başarısız olur.

// ucuncu parameter istege bağlıdır. Eğer O_CREAT kullanılmışsa bu parametre doldurulabilir.

int main()
{

   int fd;
   if( (fd = open("/home/murat/23.02.2019_", O_RDWR|O_EXCL|O_CREAT, S_IRGRP|S_IROTH )) == -1){
      perror("open");
      exit(EXIT_FAILURE);
   }



   return 0;
}

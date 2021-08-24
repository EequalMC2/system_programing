#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void exit_sys(const char* msg);

int main()
{
    char buff[BUFFER_SIZE];
    int fd;
    if ((fd = open("./pipe_driver", O_WRONLY)) == -1)
        exit_sys("open");

    for (;;) {
        char* str;
        size_t len;

        printf("Enter text:");
        fflush(stdout);
        fgets(buff, BUFFER_SIZE, stdin);

        if ((str = strchr(buff, '\n')) != NULL)
            *str = '\0';

        if (!strcmp(buff, "quit"))
            break;

        len = strlen(buff);
        if (write(fd, buff, len) == -1) {
            fprintf(stderr, "Cannot write pipe! Maybe pipe is full!\n");
            continue;
        }

        printf("%lu bytes written...\n", (unsigned long)len);
    }
    
    close(fd);

    return 0;
}

void exit_sys(const char* msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
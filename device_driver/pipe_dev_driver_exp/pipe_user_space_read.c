#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PIPE_SIZE 4096

void exit_sys(const char* msg);

int main(void)
{
    int fd;
    char buf[PIPE_SIZE + 1];
    int len;
    ssize_t result;

    if ((fd = open("./pipe_driver", O_RDONLY)) == -1)
        exit_sys("open");

    for (;;) {
        printf("How many bytes to read? ");
        fflush(stdout);
        scanf("%d", &len);
        if (!len)
            break;
        if ((result = read(fd, buf, len)) == -1)
            exit_sys("read");
        buf[result] = '\0';

        printf("%ld bytes read: \"%s\"\n", (long)result, buf);
    }

    close(fd);

    return 0;
}

void exit_sys(const char* msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
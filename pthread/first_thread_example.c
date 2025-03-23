#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *thread_proc(void *param);
void exit_sys_errno(const char*, int eno);

int main(int argc, char** argv) 
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thread_proc, NULL);
    if (ret != 0) {
        exit_sys_errno("ptread_create", ret);
    }

    for (int i = 0; i < 10; i++) {
        printf("main thread %d \n", i);
        sleep(1);
    }

    return 0;
}

void *thread_proc(void *param) {
    
    for(int i = 0; i < 10; i++) {
        printf("thread_proc %d \n", i);    
        sleep(1);
    }
}

void exit_sys_errno(const char *msg, int eno)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(eno));
}
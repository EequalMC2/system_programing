#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// int pthread_detach(pthread_t thread_id)
// this function can be called after thread is created with pthread_create function.
// if thread is not joinable or already joinable then function return EINVAL error value.
//


void *thread_proc(void *param) 
{
    for(int i = 0; i < 10; ++i) {
        printf("pthread_proc %d \n", i);
        sleep(1);
    }
}

int main() {

    pthread_t tid;
    pthread_attr_t tattr;

    int ret = pthread_attr_init(&tattr);
    if(ret != 0) {
        fprintf(stderr, "pthread attr init %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    
    ret = pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
    if(ret != 0) {
        fprintf(stderr, "ptread attr setdetachstate %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&tid, &tattr, thread_proc, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread create %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_attr_destroy(&tattr);
    if(ret != 0) {
        fprintf(stderr, "pthread attr destroy %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    } 

    printf("press ENTER to exit... \n");
    getchar();

    return 0;
}
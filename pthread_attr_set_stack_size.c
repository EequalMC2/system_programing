#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define ONE_MB 1024 * 024

void *thread_proc(void * param) 
{
    for (int i = 0; i < 10; ++i) {
        printf("thread proc %d \n", i);
        sleep(1);
    }
}

int main() 
{
    printf("started \n");

    pthread_t tid;
    pthread_attr_t tattr;

    int ret = pthread_attr_init(&tattr);
    if(ret != 0) {
        fprintf(stderr, "pthread attr init %s \n", strerror(ret));
    }

    size_t stackSize;
    ret = pthread_attr_getstacksize(&tattr, &stackSize);
    if (ret != 0) {
        fprintf(stderr, "pthread attr getstacksize %s \n", strerror(ret));
    }
    
    printf("default stack size: %lu mb \n", (stackSize / 1024) / 1024);

    stackSize = ONE_MB * 16;
    ret = pthread_attr_setstacksize(&tattr, stackSize);
    if (ret != 0) {
        fprintf(stderr, "pthread attr settackaddr %s ", strerror(ret));
    }

    ret = pthread_attr_getstacksize(&tattr, &stackSize);
    if (ret != 0) {
        fprintf(stderr, "pthread attr getstacksize %s \n", strerror(ret));
    }
    
    printf("stack size: %lu mb \n", (stackSize / 1024) / 1024);

    ret = pthread_create(&tid, NULL, thread_proc, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread create %s \n", strerror(ret));
    }

    ret = pthread_attr_destroy(&tattr);
    if (ret != 0) {
        fprintf(stderr, "pthread attr destroy %s \n", strerror(ret));
    }

    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread join %s \n", strerror(ret));
    }

    printf("finished \n");

    return 0;

}
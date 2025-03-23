#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int g_counter = 0;
int g_counter_guard_with_mutex = 0;
pthread_mutex_t g_mutex;

void* thread_proc1(void *) 
{
    for(int i = 0; i < 1000000; i++) {
        g_counter++;
    }
}

void* thread_proc2(void *) 
{
    for(int i = 0; i < 1000000; i++) {
        g_counter++;
    }
}

void* thread_proc1_mutex(void *) 
{
    for(int i = 0; i < 1000000; i++) {

        int ret = pthread_mutex_lock(&g_mutex);
        if (ret != 0) {
            fprintf(stderr, "thread_proc1_mutex pthread_mutex_lock %s \n", strerror(ret));
        }

        g_counter_guard_with_mutex++;

        ret = pthread_mutex_unlock(&g_mutex);
        if (ret != 0) {
            fprintf(stderr, "thread_proc1_mutex pthread_mutex_lock %s \n", strerror(ret));
        }
    }
}

void* thread_proc2_mutex(void *) 
{
    for(int i = 0; i < 1000000; i++) {
        int ret = pthread_mutex_lock(&g_mutex);
        if (ret != 0) {
            fprintf(stderr, "thread_proc2_mutex pthread_mutex_lock %s \n", strerror(ret));
        }

        g_counter_guard_with_mutex++;

        ret = pthread_mutex_unlock(&g_mutex);
        if (ret != 0) {
            fprintf(stderr, "thread_proc2_mutex pthread_mutex_lock %s \n", strerror(ret));
        }
    }
}

int main() {

    pthread_t tid1, tid2;
    pthread_t tid1_with_mutex, tid2_with_mutex;
    

    int ret = pthread_create(&tid1, NULL, thread_proc1, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create 1 %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&tid2, NULL, thread_proc2, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create 2 %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    
    ret = pthread_mutex_init(&g_mutex, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_mutex_init %s", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&tid1_with_mutex, NULL, thread_proc1_mutex, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create 1 %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&tid2_with_mutex, NULL, thread_proc2_mutex, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create 2 %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    
    ret = pthread_join(tid1, NULL);
    if (ret != 0) {
        fprintf(stderr, "ptread_join %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }


    ret = pthread_join(tid2, NULL);
    if (ret != 0) {
        fprintf(stderr, "ptread_join %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_join(tid1_with_mutex, NULL);
    if (ret != 0) {
        fprintf(stderr, "ptread_join %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }


    ret = pthread_join(tid2_with_mutex, NULL);
    if (ret != 0) {
        fprintf(stderr, "ptread_join %s \n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_mutex_destroy(&g_mutex);
    if(ret != 0) {
        fprintf(stderr, "pthread_mutex_destory %s \n", strerror(ret));
        exit(EXIT_FAILURE);     
    }

    printf("g_counter %d \n", g_counter);
    printf("g_counter_guard_with_mutex %d \n", g_counter_guard_with_mutex);

    return 0;
}
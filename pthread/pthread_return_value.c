#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *thread_proc(void *param);

int main(void)
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thread_proc, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "ptread_create %s", strerror(ret));
    }

    void *thread_result;
    ret = pthread_join(tid, &thread_result);
    if (ret != 0)
    {
        fprintf(stderr, "ptread_join %s", strerror(ret));
    }

    printf("result: %d \n", (int)thread_result);

    for (int i = 0; i < 10; ++i)
    {
        printf("main thread: %d \n", i);
        sleep(1);
    }

    return 0;
}

void *thread_proc(void *param)
{
    for (int i = 0; i < 10; ++i)
    {
        printf("thread proc: %d \n", i);
        // if (i == 5) {
        //     pthread_exit((void *)-1);
        // }
        sleep(1);
    }

    return (void *)0;
}
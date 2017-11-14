
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月14日 星期二 18时59分52秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void clean_up(void *arg)
{
    //printf("clean up.\n");
    pthread_mutex_unlock(&mutex);
}

void* thread_fun1(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("aaaaaaaaaaaaa\n");
    pthread_cleanup_push(clean_up, NULL);
    sleep(3);
    //pthread_exit(NULL);
    pthread_cleanup_pop(0);
    printf("bbbbbbbbbbbbb\n");
    pthread_mutex_unlock(&mutex);
}
void* thread_fun2(void *arg)
{
    pthread_t id = *(pthread_t*)arg;
    printf("This is thread 2.\n");
    sleep(1);
    pthread_cancel(id);
    pthread_exit(NULL);
}

void* thread_fun(void *arg)
{
    printf("This is thread fun.\n");
    pthread_mutex_lock(&mutex);
    printf("cccccccccccccccc\n");
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t tid1, tid2, tid;

    pthread_create(&tid1, NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, thread_fun2, &tid1);
    sleep(1);
    pthread_create(&tid, NULL, thread_fun, NULL);

    pthread_join(tid2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid, NULL);
    return 0;
}

/*
int main()
{
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread_fun1, NULL);
    printf("tid = %d\n",tid1);
    pid_t pid = fork();
    if(pid == 0)
    {
        pthread_create(&tid2, NULL, thread_fun2, &tid1);
        pthread_join(tid2, NULL);
    }
    else if(pid > 0)
    {
        pthread_join(tid1, NULL);
        int status;
        wait(&status);
    }
    return 0;
}
*/

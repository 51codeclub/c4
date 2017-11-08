
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月08日 星期三 21时09分23秒
**********************************************************/

#include"my_pthread_rwlock.h"

my_pthread_rwlock_t rwlock = MY_PTHREAD_RWLOCK_INITIALIZER;

void* thread_fun(void *arg)
{
    my_pthread_rwlock_wrlock(&rwlock);

    printf("thread fun get wrlock.\n");
    printf("thread fun sleep....\n");
    sleep(2);
    printf("thread fun wake up.\n");

    my_pthread_rwlock_unlock(&rwlock);
}

void* thread_fun1(void *arg)
{
    my_pthread_rwlock_rdlock(&rwlock);

    printf("thread 1 get rdlock\n");

    my_pthread_rwlock_unlock(&rwlock);
}
void* thread_fun2(void *arg)
{
    my_pthread_rwlock_wrlock(&rwlock);

    printf("thread 2 get wrlock\n");
    my_pthread_rwlock_unlock(&rwlock);
}

#define NUM 5
int main()
{
    pthread_t tid,tid1[NUM+5], tid2[NUM];
    pthread_create(&tid, NULL, thread_fun, NULL);
    sleep(1);
    int i;
    for(i=0; i<NUM+5; ++i)
    {
        pthread_create(&tid1[i], NULL, thread_fun1, NULL);
    }

    for(i=0; i<NUM; ++i)
    {
        pthread_create(&tid2[i], NULL, thread_fun2, NULL);
    }

    pthread_join(tid, NULL);
    for(i=0; i<NUM+5; ++i)
    {
        pthread_join(tid1[i], NULL);
    }
    for(i=0; i<NUM; ++i)
        pthread_join(tid2[i], NULL);
    return 0;
}

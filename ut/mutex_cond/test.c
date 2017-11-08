
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月08日 星期三 18时56分20秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* A_fun(void *arg)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("this A fun.\n");
    sleep(5);
    printf("A fun  wake up.\n");
    pthread_rwlock_unlock(&rwlock);
}
//2 4 6 8 10
void* B_fun(void *arg)
{
    pthread_rwlock_wrlock(&rwlock);
    printf("this B fun.\n");
    pthread_rwlock_unlock(&rwlock);
}

int main()
{
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL , A_fun, NULL);
    sleep(1);
    pthread_create(&tid2, NULL , B_fun, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}

/*
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t is_even = PTHREAD_COND_INITIALIZER;
pthread_cond_t is_uneven = PTHREAD_COND_INITIALIZER;

#define SIZE 10
static int count = 1;

//1 3 5 7 9
void* A_fun(void *arg)
{
    while(count <= SIZE)
    {
        pthread_mutex_lock(&mutex);
        if(count % 2 == 1)
        {
            printf("In A fun: %d\n",count);
            count++;
            pthread_cond_signal(&is_even);
        }
        else
            pthread_cond_wait(&is_uneven, &mutex);
        pthread_mutex_unlock(&mutex);
    }
}
//2 4 6 8 10
void* B_fun(void *arg)
{
    while(count <= SIZE)
    {
        pthread_mutex_lock(&mutex);
        if(count % 2 == 0)
        {
            printf("In B fun: %d\n",count);
            count++;
            pthread_cond_signal(&is_uneven);
        }
        else
            pthread_cond_wait(&is_even, &mutex);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t tid1, tid2;

    pthread_create(&tid2, NULL , B_fun, NULL);
    pthread_create(&tid1, NULL , A_fun, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}


/*
void* thread_fun1(void *arg)
{
    int index = *(int*)arg;
    pthread_mutex_lock(&mutex);
    printf("[%d] thread wait.....\n", index);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t tid1[MAX_THREAD_NUM], tid2;
    int i;
    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        pthread_create(&tid1[i], NULL, thread_fun1, &i);
        sleep(1);
    }

    //pthread_cond_signal(&cond);
    pthread_cond_broadcast(&cond);

    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        pthread_join(tid1[i], NULL);
        printf("[%d] thread finish.\n", i);
    }
    return 0;
}

/*
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond, cond1;

void* thread_fun1(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("This is thread 1.\n");
    //sleep(3);
    pthread_cond_wait(&cond, &mutex);
    printf("thread 1 wake up.\n");
    pthread_mutex_unlock(&mutex);
}
void* thread_fun2(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("This is thread 2.\n");
    sleep(3);
    printf("thread 2 signal.\n");
    pthread_cond_signal(&cond);

    sleep(3);
    printf("thread 2 wake up.\n");

    pthread_mutex_unlock(&mutex);

}

int main()
{
    pthread_cond_init(&cond, NULL);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, thread_fun2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_cond_destroy(&cond);
    return 0;
}
*/

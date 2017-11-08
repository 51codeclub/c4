
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月07日 星期二 19时32分03秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define MAX_THREAD_NUM 3

void* thread_fun(void *arg)
{
    int index = *(int*)arg;
    printf("[%d] thread start up.\n",index);
    
    //char buffer[64];
    //memset(buffer, 0, 64);
    //sprintf(buffer,"[%d] thread finish.", index);

    //pthread_exit(buffer);
    //printf("[%d]thread buffer = %s\n",index, buffer);
    if(index == 0)
        pthread_exit("[0] thread finish.");
    else if(index == 1)
        pthread_exit("[1] thread finish.");
    else if(index == 2)
        pthread_exit("[2] thread finish.");
}

int main()
{
    pthread_t tid[MAX_THREAD_NUM];
    int i;
    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        pthread_create(&tid[i], NULL, thread_fun, &i);
        sleep(1);
    }
    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        char *retval;
        pthread_join(tid[i], (void**)&retval);
        printf("%s\n",retval);
    }
    return 0;
}



/*
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;

void* thread_fun1(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("I am thread 1.\n");
    pthread_cond_wait(&cond, &mutex); 
    printf("thread 1 wake up.\n");
    //pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
void* thread_fun2(void *arg)
{
    int ret = pthread_mutex_lock(&mutex);
    if(ret != 0)
    {
        printf("thread 2 lock mutex error.\n");
    }
    else
        printf("thread 2 lock mutex OK.\n");
    pthread_t tid = *(pthread_t*)arg;
    printf("I am thread 2.\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, thread_fun2, &tid1);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}



/*
void* thread_fun1(void *arg)
{
    printf("I am thread 1.\n");
    sleep(3);
    printf("thread 1 wake up.\n");
    pthread_exit(NULL);
}
void* thread_fun2(void *arg)
{
    pthread_t tid = *(pthread_t*)arg;
    printf("I am thread 2.\n");
    pthread_cancel(tid);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, thread_fun2, &tid1);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}

/*
#define MAX_THREAD_NUM 5

void* thread_fun(void *arg)
{
    sleep(10);
    int index = *(int*)arg;
    printf("[%d] thread start up.\n",index);

    char buffer[128];
    memset(buffer, 0, 128);
    sprintf(buffer,"[%d] thread finish.", index);
    pthread_exit(buffer);
}

int main()
{
    pthread_t tid[MAX_THREAD_NUM];
    int i;
    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        pthread_create(&tid[i], NULL, thread_fun, &i);
        sleep(1);
    }
    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        char *retval;
        pthread_join(tid[i], (void**)&retval);
        printf("%s\n",retval);
    }
    return 0;
}

/*
void* thread_fun(void *arg)
{
    int n = *(int*)arg;
    printf("in thread fun tid = %d\n",pthread_self());
    int i;
    for(i = 0; i<n; ++i)
     {
        printf("This is Child Thread.\n");
    }
    char *str = "child thread exit code: i am child thread.";
    pthread_exit(str);
}

int main()
{
    printf("thread id = %d\n",pthread_self());

    pthread_t tid;
    int n = 5;
    int ret = pthread_create(&tid, NULL, thread_fun, &n);
    if(ret != 0)
    {
        perror("pthread_create");
        exit(1);
    }
    else
        printf("in main thread tid = %d\n",tid);

    int i;
    for(i=0; i<10; ++i)
    {
        printf("This is Main Thread.\n");
    }

    char *retval;
    pthread_join(tid, (void**)&retval);
    printf("exit code:> %s\n",retval);
    return 0;
}

/*
int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("This Child Process.\n");
        sleep(3);
        printf("child process finish\n");
    }
    else if(pid > 0)
    {
        printf("This is parent process.\n");
        sleep(1);
        printf("parent process finish.\n");
    }
    return 0;
}
*/

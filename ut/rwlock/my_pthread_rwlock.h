#ifndef _MY_PTHREAD_RWLOCK_H
#define _MY_PTHREAD_RWLOCK_H
/**********************************************************
*    > File Name: my_pthread_rwlock.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月08日 星期三 20时10分08秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

//my_pthread_rwlock_t rwlock = MY_PTHREAD_RWLOCK_INITIALIZER;

enum{EINVAL};

typedef struct
{
    pthread_mutex_t rw_mutex;
    pthread_cond_t  rw_condreaders;
    pthread_cond_t  rw_condwriters;
    int rw_magic;
    int rw_nwaitreaders;
    int rw_nwaitwriters;
    int rw_refcount; //-1 0  n>0
}my_pthread_rwlock_t;

#define RW_MAGIC 0x20171118

#define MY_PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER,\
                                        PTHREAD_COND_INITIALIZER,\
                                        PTHREAD_COND_INITIALIZER,\
                                        RW_MAGIC,\
                                        0,0,0}

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw);
///////////////////////////////////////////////////////

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;

    while(rw->rw_refcount<0 || rw->rw_nwaitwriters>0)
    {
        rw->rw_nwaitreaders++;
        result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
        rw->rw_nwaitreaders--;
        if(result != 0)
            break;
    }
    if(result == 0)
        rw->rw_refcount++;

    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}

int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if((result=pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;

    while(rw->rw_refcount != 0)
    {
        rw->rw_nwaitwriters++;
        result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
        rw->rw_nwaitwriters--;
        if(result != 0)
            break;
    }
    if(result == 0)
        rw->rw_refcount = -1;

    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}

int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;

    if(rw->rw_refcount == -1)
        rw->rw_refcount = 0;
    else if(rw->rw_refcount > 0)
        rw->rw_refcount--;
    else
    {
        printf("unlock rwlock error.\n");
        exit(1);
    }
    if(rw->rw_nwaitwriters > 0)
    {
        if(rw->rw_refcount == 0)
            result = pthread_cond_signal(&rw->rw_condwriters);
    }
    else if(rw->rw_nwaitreaders > 0)
        result = pthread_cond_broadcast(&rw->rw_condreaders);

    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}


#endif // _MY_PTHREAD_RWLOCK_H















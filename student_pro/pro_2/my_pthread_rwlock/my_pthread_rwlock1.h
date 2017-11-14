#ifndef _MY_PTHREAD_RWLOCK_
#define _MY_PTHREAD_RWLOCK_
//写优先

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define RW_MAGIC 20171111
#define MY_PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER,\
									   PTHREAD_COND_INITIALIZER,\
									   PTHREAD_COND_INITIALIZER,\
									   0,0,0,RW_MAGIC}
enum{EINVAL};

typedef struct my_pthread_rwlock_t
{
	pthread_mutex_t rwlock_mutex;
	pthread_cond_t rw_condreaders;
	pthread_cond_t rw_condwriters;
	int rw_recount;
	int rw_nwaitreaders;
	int rw_nwaitwriters;
	int rw_magic;
}my_pthread_rwlock_t;

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw);

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw)
{
	int result;
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if((result = pthread_mutex_lock(&rw->rwlock_mutex)) != 0)
		return result;

	while(rw->rw_recount < 0 || rw->rw_nwaitwriters >0)
	{
		rw->rw_nwaitreaders++;
		result=pthread_cond_wait(&rw->rw_condreaders,&rw->rwlock_mutex);
		rw->rw_nwaitreaders--;
		if(result != 0)
			break;
	}

	if(result == 0)
	rw->rw_recount++;

	pthread_mutex_unlock(&rw->rwlock_mutex);
	return result;
}

int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw)
{
	int result;
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(result = pthread_mutex_lock(&rw->rwlock_mutex) != 0)
		return result;

	while(rw->rw_recount != 0)
	{
		rw->rw_nwaitwriters++;
		result = pthread_cond_wait(&rw->rw_condwriters,&rw->rwlock_mutex);
		rw->rw_nwaitwriters--;
		if(result != 0)
			break;
	}

	if(result == 0)
		rw->rw_recount = -1;

	pthread_mutex_unlock(&rw->rwlock_mutex);
	return result;
}


int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw)
{
	int result;
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if((result = pthread_mutex_lock(&rw->rwlock_mutex)) !=0)
		return result;

	if(rw->rw_recount == -1)
		rw->rw_recount = 0;
	else if(rw->rw_recount > 0)
		rw->rw_recount--;
	else
	{
		printf("unlock error!\n");
		exit(1);
	}

	if(rw->rw_nwaitwriters > 0)
	{
		if(rw->rw_recount == 0)
		result = pthread_cond_signal(&rw->rw_condwriters);
	}
	else if(rw->rw_nwaitreaders > 0)
		result = pthread_cond_broadcast(&rw->rw_condreaders);

	pthread_mutex_unlock(&rw->rwlock_mutex);
	return result;
}

#endif

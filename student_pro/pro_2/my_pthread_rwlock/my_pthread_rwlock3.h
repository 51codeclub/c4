#ifndef _MY_PTHREAD_RWLOCK_
#define _MY_PTHREAD_RWLOCK_
//写优先

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define RW_MAGIC 20171111
#define MY_PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER,\
									   PTHREAD_COND_INITIALIZER,\
									   PTHREAD_COND_INITIALIZER,\
									   0,0,0,RW_MAGIC}
enum{EINVAL,EBUSY};

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

typedef int my_pthread_rw_attr_t;

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_init(my_pthread_rwlock_t *rw,my_pthread_rw_attr_t *attr);
int my_pthread_rwlock_destroy(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *rw);

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
		//exit(1);
		return 0;
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

int my_pthread_rwlock_init(my_pthread_rwlock_t *rw,my_pthread_rw_attr_t *attr)
{
	int result;

	if (attr != NULL)
		return EINVAL;   /*not supported*/
	if((result = pthread_mutex_init(&rw->rwlock_mutex,NULL)) != 0)
		goto err1;
	if((result =pthread_cond_init(&rw->rw_condreaders,NULL)) != 0)
		goto err2;
	if((result =pthread_cond_init(&rw->rw_condwriters,NULL)) != 0)
		goto err3;
	rw->rw_nwaitreaders = 0;
	rw->rw_nwaitreaders = 0;
	rw->rw_recount  = 0;
	rw->rw_magic = RW_MAGIC;
	return(0);
err3:
	pthread_cond_destroy(&rw->rw_condreaders);
err2:
	pthread_mutex_destroy(&rw->rwlock_mutex);
err1:
	return(result);
}

int my_pthread_rwlock_destroy(my_pthread_rwlock_t *rw)
{
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(rw->rw_recount != 0 ||rw-> rw_nwaitwriters != 0 ||rw->rw_nwaitreaders != 0)
		return EBUSY;

	pthread_mutex_destroy(&rw->rwlock_mutex);
	pthread_cond_destroy(&rw->rw_condwriters);
	pthread_cond_destroy(&rw->rw_condreaders);
	rw->rw_magic=0;

	return 0;
}

int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *rw)
{
	int result;
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if((result = pthread_mutex_lock(&rw->rwlock_mutex)) != 0)
		return result;
	if(rw->rw_recount < 0 || rw->rw_nwaitwriters > 0)
	{
		printf("EBUSY\n");
		result = EBUSY;
	}

	else 
	rw->rw_recount++;

	pthread_mutex_unlock(&rw->rwlock_mutex);
	return result;
}

int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *rw)
{
	int result;
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if((result = pthread_mutex_lock(&rw->rwlock_mutex)) != 0)
		return result;
	if(rw->rw_recount != 0)
	{
		printf("EBUSY\n");
		return EBUSY;
	}
	else
		rw->rw_recount = 0;

	pthread_mutex_unlock(&rw->rwlock_mutex);
	return result;
}

#endif

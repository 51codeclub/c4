#include"my_pthread_rwlock3.h"
//写优先

my_pthread_rwlock_t rwlock = MY_PTHREAD_RWLOCK_INITIALIZER;

void* thread1(void* arg)
{
	my_pthread_rwlock_rdlock(&rwlock);
	printf("thread1 wrlock was sleep!\n");
	sleep(3);
	printf("thread1 wrlock wake up\n");
	my_pthread_rwlock_unlock(&rwlock);
}

void* thread2(void* arg)
{
	//my_pthread_rwlock_rdlock(&rwlock->rw_mutex);
	my_pthread_rwlock_tryrdlock(&rwlock);
	printf("thread2 tryrdlock !\n");
	my_pthread_rwlock_unlock(&rwlock);
}

void* thread3(void *arg)
{
	my_pthread_rwlock_tryrdlock(&rwlock);
	printf("thread3 tryrdlock\n");
	my_pthread_rwlock_unlock(&rwlock);
}

int main()
{
	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,thread1,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,thread2,NULL);
	pthread_create(&tid3,NULL,thread3,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	return 0;
}

#include"my_pthread_rwlock3.h"
#include<unistd.h>
#include<string.h>

//验证写优先

//my_pthread_rwlock_t rwlock=MY_PTHREAD_RWLOCK_INITIALIZER;

my_pthread_rwlock_t rwlock;


void* thread1(void* arg)
{
	my_pthread_rwlock_wrlock(&rwlock);
	printf("I an the thread1 wrlock\n");
	printf("thread1 is in wrlock!\n");
	sleep(2);
	printf("thread1 is wake up!\n");
	my_pthread_rwlock_unlock(&rwlock);
}

void* thread2(void* arg)
{
	my_pthread_rwlock_wrlock(&rwlock);
	printf("I am wrlock!\n");
	my_pthread_rwlock_unlock(&rwlock);
}


void* thread3(void* arg)
{
	my_pthread_rwlock_rdlock(&rwlock);
	printf("I am rdlock!\n");
	my_pthread_rwlock_unlock(&rwlock);
}

int main()
{
	my_pthread_rwlock_init(&rwlock,NULL);
	pthread_t tid,tid1,tid2;
	pthread_create(&tid,NULL,thread1,NULL);
	sleep(1);
	pthread_create(&tid1,NULL,thread3,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);
    pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	my_pthread_rwlock_destroy(&rwlock);
	return 0;
}


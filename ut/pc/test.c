
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月14日 星期二 19时51分21秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

#define MAX_COUNT 20
#define BUFFER_SIZE 8
#define OVER -1

typedef struct pc_st
{
    int buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t  notfull;
    pthread_cond_t  notempty;
    int write_pos;
    int read_pos;
}pc_st;

pc_st pc;
void init_pc(pc_st *pt)
{
    memset(pt->buffer, 0, sizeof(pt->buffer));
    pthread_mutex_init(&pt->mutex, NULL);
    pthread_cond_init(&pt->notfull, NULL);
    pthread_cond_init(&pt->notempty, NULL);
    pt->write_pos = 0;
    pt->read_pos = 0;
}
void destroy_pc(pc_st *pt)
{ 
    memset(pt->buffer, 0, sizeof(pt->buffer));
    pthread_mutex_destroy(&pt->mutex);
    pthread_cond_destroy(&pt->notfull);
    pthread_cond_destroy(&pt->notempty);
    pt->write_pos = 0;
    pt->read_pos = 0;
}

void put(pc_st *pt, int key)
{
    //pthread_mutex_lock(&pt->mutex);

    pt->buffer[pt->write_pos] = key;
    pt->write_pos++;

    //pthread_mutex_unlock(&pt->mutex);
}
int get(pc_st *pt)
{
    int value;
    //pthread_mutex_lock(&pt->mutex);
    value = pt->buffer[pt->read_pos];
    pt->read_pos++;
    //pthread_mutex_unlock(&pt->mutex);
    return value;
}

void* producer(void *arg)
{
    int i;
    for(i=1; i<= MAX_COUNT; ++i)
    {
        put(&pc, i);
    }
    put(&pc, OVER);
}
void* consumer(void *arg)
{
    int value;
    while(1)
    {
        value = get(&pc);
        if(value == OVER)
            break;
        printf("value = %d\n",value);
        sleep(1);
    }
}

int main()
{
    init_pc(&pc);
    pthread_t pro_id, con_id;
    pthread_create(&pro_id, NULL, producer, NULL);
    sleep(1);
    pthread_create(&con_id, NULL, consumer, NULL);

    pthread_join(pro_id, NULL);
    pthread_join(con_id, NULL);
    destroy_pc(&pc);
    return 0;
}

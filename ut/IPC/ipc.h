#ifndef _IPC_H
#define _IPC_H
/**********************************************************
*    > File Name: ipc.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月31日 星期二 20时47分21秒
**********************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

key_t Ftok(const char *pathname, int proj_id)
{
    key_t key = ftok(pathname, proj_id);
    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }
    return key;
}

int Semget(key_t key, int nsems, int semflg)
{
    int id = semget(key, nsems, semflg);
    if(id == -1)
    {
        perror("semget");
        exit(1);
    }
    return id;
}

#endif // _IPC_H













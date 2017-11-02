
/**********************************************************
*    > File Name: set_sem.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月01日 星期三 19时01分42秒
**********************************************************/

#include"../ipc.h"

// ./set_sem mysem 0xff 5

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("<Warning Usage>:%s pathname proj_id sem_val\n",argv[0]);
        return -1;
    }

    key_t sem_key = Ftok(argv[1], atoi(argv[2]));
    int sem_id = Semget(sem_key, 0, 0);

    union semun sem_val;
    sem_val.val = atoi(argv[3]);
    int ret = semctl(sem_id, 0, SETVAL, sem_val);
    if(ret == -1)
        printf("Set Sem Fail.\n");
    else
        printf("Set Sem Success.\n");

    return 0;
}

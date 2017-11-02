
/**********************************************************
*    > File Name: set_sem.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月01日 星期三 19时01分42秒
**********************************************************/

#include"../ipc.h"

// ./set_sem mysem 0xff

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("<Warning Usage>:%s pathname proj_id\n",argv[0]);
        return -1;
    }

    key_t sem_key = Ftok(argv[1], atoi(argv[2]));
    int sem_id = Semget(sem_key, 0, 0);

    int sem_val = semctl(sem_id, 0, GETVAL);
    if(sem_val == -1)
        printf("get Sem Fail.\n");
    else
        printf("Sem Value = %d\n",sem_val);

    return 0;
}

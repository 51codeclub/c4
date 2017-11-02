
/**********************************************************
*    > File Name: remove_sem.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月01日 星期三 18时54分23秒
**********************************************************/

#include"../ipc.h"

//   ./remove_sem pathname  proj_id

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("<Warning Usage>: %s pathname proj_id\n",argv[0]);
        return -1;
    }
    key_t sem_key = Ftok(argv[1], atoi(argv[2]));

    int sem_id = Semget(sem_key, 0, 0);

    int ret = semctl(sem_id, 0, IPC_RMID);
    if(ret == -1)
        printf("Remove Sem Fail.\n");
    else
        printf("Remove Sem Success.\n");

    return 0;
}

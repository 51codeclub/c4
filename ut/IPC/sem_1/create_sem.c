
/**********************************************************
*    > File Name: create_sem.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月01日 星期三 18时47分02秒
**********************************************************/

#include"../ipc.h"

//  ./create_sem mysem 0xff 2
int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("<Warning, Usage>: %s pathname proj_id sem_ini_val\n", argv[0]);
        return -1;
    }
    key_t sem_key = Ftok(argv[1], atoi(argv[2]));
    int sem_id = Semget(sem_key, 1, IPC_CREAT|IPC_EXCL|0755);

    union semun init;
    init.val = atoi(argv[3]);

    semctl(sem_id, 0, SETVAL, init);
    printf("Create Sem OK.\n");
    return 0;
}

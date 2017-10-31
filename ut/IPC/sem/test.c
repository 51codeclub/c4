
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月31日 星期二 20时49分27秒
**********************************************************/

#include"../ipc.h"

int main()
{
    key_t key = Ftok("mysem", 0xff);
    int sem_id = Semget(key, 5, IPC_CREAT|IPC_EXCL|0755);

    union semun init;
    init.val = 3;
    semctl(sem_id, 0, SETVAL, init);

    int sem_val = semctl(sem_id, 0, GETVAL);
    printf("sem value = %d\n",sem_val);

    struct sembuf op;
    op.sem_num = 0;
    op.sem_op =  2;
    op.sem_flg = 0;
    semop(sem_id, &op, 1);
    
    sem_val = semctl(sem_id, 0, GETVAL);
    printf("sem value = %d\n",sem_val);

    int ret = semctl(sem_id, 3, IPC_RMID);
    if(ret == -1)
        printf("Remove sem Fail.\n");
    else
        printf("Remove sem Success.\n");
    return 0;
}


/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月01日 星期三 19时25分25秒
**********************************************************/

#include"../ipc.h"

int main(int argc, char *argv[])
{
    key_t shm_key = Ftok(argv[1], atoi(argv[2]));
    int shm_id = Shmget(shm_key, 1024, IPC_CREAT|IPC_EXCL|0755);

    char *addr = (char*)shmat(shm_id, NULL, 0);
    if((void*)addr == (void*)-1)
    {
        shmctl(shm_id, IPC_RMID, NULL);
        return -1;
    }

    ////////////////////////////////////////////////////////
    int sem_id = Semget(shm_key, 2, IPC_CREAT|IPC_EXCL|0755);
    union semun init;
    init.val = 0;
    semctl(sem_id, 0, SETVAL, init);
    semctl(sem_id, 1, SETVAL, init);

    struct sembuf p = {1,-1,0};
    struct sembuf v = {0, 1, 0};

    while(1)
    {
        printf("Ser:>");
        scanf("%s",addr);
        if(!strcmp(addr, "quit"))
            break;
        semop(sem_id, &v, 1);

        semop(sem_id, &p, 1);
        printf("Cli:>%s\n",addr);
    }

    shmdt(addr);
    semctl(sem_id, 0, IPC_RMID);
    shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}


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
    int shm_id = Shmget(shm_key, 0, 0);

    char *addr = (char*)shmat(shm_id, NULL, 0);
    if((void*)addr == (void*)-1)
    {
        perror("shmat");
        return -1;
    }

    int sem_id = Semget(shm_key, 0, 0);
    struct sembuf p = {0, -1, 0};
    struct sembuf v = {1, 1, 0};
    while(1)
    {
        semop(sem_id, &p, 1);
        printf("Ser:>%s\n",addr);
        printf("Cli:>");
        scanf("%s",addr);
        if(!strcmp(addr, "quit"))
            break;
        semop(sem_id, &v, 1);
    }

    shmdt(addr);

    return 0;
}

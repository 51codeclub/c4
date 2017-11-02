
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月01日 星期三 21时12分32秒
**********************************************************/

#include"../ipc.h"
#include"utili.h"


int main(int argc, char *argv[])
{
    key_t msg_key = Ftok(argv[1], atoi(argv[2]));
    int msg_id = msgget(msg_key, IPC_CREAT|IPC_EXCL|0755);
    if(msg_id == -1)
    {
        printf("msgget");
        exit(1);
    }

    Msg msg;

    while(1)
    {
        printf("Ser:>");
        scanf("%s",msg.msg_text);
        msg.msg_type = SER_SND_FLG;
        msgsnd(msg_id, &msg, strlen(msg.msg_text)+1, 0);

        msgrcv(msg_id, &msg, MSG_BUFFER_SIZE, SER_RCV_FLG, 0);
        printf("Cli:>%s\n",msg.msg_text);
    }

    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}

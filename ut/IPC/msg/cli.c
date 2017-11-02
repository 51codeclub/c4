
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
    int msg_id = msgget(msg_key, 0);

    Msg msg;
    while(1)
    {
        msgrcv(msg_id, &msg, MSG_BUFFER_SIZE, CLI_RCV_FLG, 0);
        printf("Ser:>%s\n",msg.msg_text);
        
        printf("Cli:>");
        scanf("%s",msg.msg_text);
        msg.msg_type = CLI_SND_FLG;
        msgsnd(msg_id, &msg, strlen(msg.msg_text)+1, 0);
    }

    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}

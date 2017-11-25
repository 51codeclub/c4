
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月25日 星期六 18时37分04秒
**********************************************************/

#include"../socket.h"

// ./ser ip port

int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr);
    int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
    if(sockConn == -1)
    {
        printf("Server Accept Client Connect Fail.\n");
        exit(1);
    }
    else
    {
        printf("Server Accept Client Connect Success\n");
    }

    char sendbuf[256];
    char recvbuf[256];
    while(1)
    {
        printf("Ser:>");
        scanf("%s",sendbuf);
        send(sockConn, sendbuf, strlen(sendbuf)+1, 0);
        recv(sockConn, recvbuf, 256, 0);
        printf("Cli:>%s\n",recvbuf);
    }

    close(sockSer);
    return 0;
}






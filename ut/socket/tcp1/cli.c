
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月25日 星期六 18时37分04秒
**********************************************************/

#include"utili.h"

// ./ser ip port

int main(int argc, char *argv[])
{
    int sockCli = socket(AF_INET, SOCK_STREAM, 0);
    if(sockCli == -1)
    {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(atoi(argv[2]));
    addrSer.sin_addr.s_addr = inet_addr(argv[1]);

    socklen_t addrlen = sizeof(struct sockaddr);

    int ret = connect(sockCli, (struct sockaddr*)&addrSer, addrlen);
    if(ret == -1)
    {
        printf("Client Connect Server Fail.\n");
    }
    else
    {
        printf("Client Connect Server Success.\n");
    }

    char sendbuf[256];
    char recvbuf[256];
    while(1)
    {
        recv(sockCli, recvbuf, 256, 0);
        printf("Ser:>%s\n",recvbuf);
        printf("Cli:>");
        scanf("%s",sendbuf);
        send(sockCli, sendbuf, strlen(sendbuf)+1, 0);
    }

    close(sockCli);
    return 0;
}






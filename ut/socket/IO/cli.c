
/**********************************************************
*    > File Name: cli.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月21日 星期二 19时56分56秒
**********************************************************/

#include"../utili.h"

int main()
{
    int sockCli = socket(AF_INET, SOCK_STREAM, 0);
    if(sockCli == -1)
    {
        perror("socket.");
        exit(1);
    }

    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t len = sizeof(struct sockaddr);
    int ret = connect(sockCli, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        perror("connect.");
    }
    else
    {
        printf("Client Connect Server Success.\n");
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while(1)
    {
        printf("Cli:>");
        scanf("%s",sendbuf);
        if(!strcmp(sendbuf,"quit"))
            break;
        send(sockCli, sendbuf, strlen(sendbuf)+1, 0);
        recv(sockCli, recvbuf, BUFFER_SIZE, 0);
        printf("Form Self Msg:> %s\n",recvbuf);
        
    }

    close(sockCli);
    return 0;
}









/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月25日 星期六 18时55分59秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int sockSer = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockSer == -1)
    {
        perror("socket.");
        exit(1);
    }

    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t addrlen = sizeof(struct sockaddr);
    int ret = bind(sockSer, (struct sockaddr*)&addrSer, addrlen);
    if(ret == -1)
    {
        perror("bind");
        exit(1);
    }

    char sendbuf[128];
    char recvbuf[128];

    struct sockaddr_in addrCli;
    while(1)
    {
        recvfrom(sockSer, recvbuf, 128, 0, (struct sockaddr*)&addrCli, &addrlen);
        printf("form client msg:> %s\n", recvbuf);
        sendto(sockSer, recvbuf, strlen(recvbuf)+1, 0, (struct sockaddr*)&addrCli, addrlen);
    }

    close(sockSer);
    return 0;

}








/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月28日 星期二 19时13分52秒
**********************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<poll.h>

#define MAX_CLIENT_SIZE 5

int main()
{
    int sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockSer == -1)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    int yes = 1;
    setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    socklen_t addrlen = sizeof(struct sockaddr);
    int ret = bind(sockSer, (struct sockaddr*)&addrSer, addrlen);
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }

    ret = listen(sockSer, 5);
    if(ret == -1)
    {
        perror("listen");
        return -1;
    }

    char buffer[128];

    struct pollfd client_fd[MAX_CLIENT_SIZE+1];
    client_fd[0].fd = sockSer;
    client_fd[0].events = POLLIN;

    int i;
    for(i=1; i<=MAX_CLIENT_SIZE; ++i)
    {
        client_fd[i].fd = 0;
    }

    int numfd = 1;
    while(1)
    {
        int ret = poll(client_fd, numfd, 3000);
        if(ret == -1)
        {
            perror("poll");
            continue;
        }
        else if(ret == 0)
        {
            printf("time out.\n");
            continue;
        }
        else
        {
            if(client_fd[0].fd==sockSer && (client_fd[0].revents&POLLIN))
            {
                int sockConn = accept(client_fd[0].fd, (struct sockaddr*)&addrCli, &addrlen);
                if(sockConn == -1)
                {
                    perror("accept");
                    continue;

                }
                
                for(i=1; i<=MAX_CLIENT_SIZE; ++i)
                {
                    if(client_fd[i].fd == 0)
                    {
                        client_fd[i].fd = sockConn;
                        client_fd[i].events = POLLIN;
                        numfd++;
                        break;
                    }
                }
                if(i >= MAX_CLIENT_SIZE)
                {
                    printf("Server Over Load.\n");
                }
                else
                    printf("A New Client Come.....\n");
            }
            else
            {
                for(i=1; i<=MAX_CLIENT_SIZE; ++i)
                {
                    if(client_fd[i].fd!=0 && (client_fd[i].revents&POLLIN))
                    {
                        recv(client_fd[i].fd, buffer, 128, 0);
                        printf("client msg:> %s\n",buffer);
                        send(client_fd[i].fd, buffer, strlen(buffer)+1, 0);
                    }
                }
            }
        }
    }

    close(sockSer);
    return 0;
}










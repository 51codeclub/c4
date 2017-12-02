
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
#include<sys/epoll.h>

#define MAX_CLIENT_SIZE 5

//

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

    int epoll_fd = epoll_create(MAX_CLIENT_SIZE+1);

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockSer;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockSer, &ev);

    int i;
    struct epoll_event revent[MAX_CLIENT_SIZE];
    while(1)
    {
        int ret = epoll_wait(epoll_fd, revent, MAX_CLIENT_SIZE, -1);
        if(ret == -1)
        {
            perror("epoll_wait.");
            continue;
        }
        else if(ret == 0)
        {
            printf("time out.\n");
            continue;
        }
        else
        {
            for(i=0; i<ret; ++i)
            {
                if(revent[i].data.fd==sockSer && (revent[i].events & EPOLLIN))
                {
                    int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
                    if(sockConn == -1)
                    {
                        perror("accept.");
                        break;
                    }

                    ev.events = EPOLLIN;
                    ev.data.fd = sockConn;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockConn, &ev);
                    printf("New Client Come...\n");
                }
                else if(revent[i].events & EPOLLIN)
                {
                    recv(revent[i].data.fd, buffer, 128, 0);
                    send(revent[i].data.fd, buffer, strlen(buffer)+1, 0);
                }

            }
        }
    }

    close(sockSer);
    return 0;
}










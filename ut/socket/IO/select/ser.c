
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
#include<sys/select.h>

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
    int client_fd[MAX_CLIENT_SIZE] = {0};
    int client_conn_num = 0;
    int i;
    fd_set set;

    int max_sock = sockSer;

    while(1)
    {

        FD_ZERO(&set);
        FD_SET(sockSer, &set);
        for(i=0; i<MAX_CLIENT_SIZE; ++i)
        {
            if(client_fd[i] != 0)
            {
                FD_SET(client_fd[i], &set);
            }
        }

        int ret = select(max_sock+1, &set, NULL, NULL, NULL); //阻塞
        if(ret == -1)
        {
            perror("select");
            continue;
        }
        else if(ret == 0)
        {
            printf("Time Out.\n");
            continue;
        }
        else
        {
            if(FD_ISSET(sockSer, &set))
            {
                //accept
                int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
                if(sockConn == -1)
                {
                    perror("accept");
                    continue;
                }

                if(sockConn > max_sock)
                    max_sock = sockConn;
                client_conn_num++;
                for(i=0; i<MAX_CLIENT_SIZE; ++i)
                {
                    if(client_fd[i] == 0)
                    {
                        client_fd[i] = sockConn;
                        break;
                    }
                }
                if(i >= MAX_CLIENT_SIZE)
                {
                    printf("Server Over Load.\n");
                }
                else
                {
                    printf("New Client Come Baby.\n");
                }
            }
            else
            {
                for(i=0; i<MAX_CLIENT_SIZE; ++i)
                {
                    if(client_fd[i]!=0 && FD_ISSET(client_fd[i], &set))
                    {
                        int recvbyte = recv(client_fd[i], buffer, 128, 0);
                        if(recvbyte <= 0)
                        {
                            printf("Recv Data Error.\n");
                        }
                        int sendbyte = send(client_fd[i], buffer, strlen(buffer)+1, 0);
                        if(sendbyte <= 0)
                        {
                            printf("Send Data Error.\n");
                        }
                        break;
                    }
                }
            }
        }
    }

    close(sockSer);
    return 0;
}










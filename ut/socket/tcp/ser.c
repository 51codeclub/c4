
/**********************************************************
 *    > File Name: ser.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年11月21日 星期二 19时38分05秒
 **********************************************************/

#include"../utili.h"

int main()
{
    int sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockSer == -1)
    {
        perror("socket.");
        exit(1);
    }

    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    int yes = 1;
    setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    socklen_t len = sizeof(struct sockaddr);
    int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        perror("bind.");
        exit(1);
    }

    ret = listen(sockSer, LISTEN_QUEUE_SIZE);
    if(ret == -1)
    {
        perror("listen.");
        exit(1);
    }

    printf("Server wait Client Connect......\n");

    /*int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
      if(sockConn == -1)
      {
      printf("Server Accept Client Connect Fail.\n");
      exit(1);
      }
      else
      {
      printf("Server Accept Client Connect Success.\n");
      printf("Client IP:> %s\n", inet_ntoa(addrCli.sin_addr));
      printf("Client Port:> %d\n", addrCli.sin_port);
      }
      */
    int sockConn;

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while(1)
    {
        sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
        if(sockConn == -1)
        {
            printf("Server Accept Client Connect Fail.\n");
            exit(1);
        }
        else
        {
            printf("Server Accept Client Connect Success.\n");
            printf("Client IP:> %s\n", inet_ntoa(addrCli.sin_addr));
            printf("Client Port:> %d\n", addrCli.sin_port);
        }
        printf("Ser:>");
        scanf("%s",sendbuf);
        if(!strcmp(sendbuf, "quit"))
            break;
        send(sockConn, sendbuf, strlen(sendbuf)+1, 0);
        recv(sockConn, recvbuf, BUFFER_SIZE, 0);
        printf("Cli:> %s\n", recvbuf);
    }

    close(sockSer);
    return 0;
}







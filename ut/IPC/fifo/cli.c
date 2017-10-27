
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月27日 星期五 21时19分47秒
**********************************************************/
#include"utili.h"

int main()
{
    int read_fd = open(write_fifo, O_RDONLY);
    if(read_fd == -1)
    {
        perror("open read fifo");
        exit(1);
    }

    int ret = mkfifo(read_fifo, O_CREAT|O_EXCL|0755);
    if(ret == -1)
    {
        perror("mkfifo");
        close(read_fd);
        exit(1);
    }

    int write_fd = open(read_fifo, O_WRONLY);
    if(write_fd == -1)
    {
        perror("open write fiof");
        exit(1);
    }
    
    char sendbuf[256];
    char recvbuf[256];
    while(1)
    {
        read(read_fd, recvbuf, 256);
        printf("Ser:>%s\n",recvbuf);

        printf("Cli:>");
        scanf("%s",sendbuf);
        write(write_fd, sendbuf, strlen(sendbuf)+1);
    }
    close(write_fd);
    close(read_fd);
    return 0;
}







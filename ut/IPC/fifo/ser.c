
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月27日 星期五 21时19分47秒
**********************************************************/
#include"utili.h"

int main()
{
    int ret = mkfifo(write_fifo, O_CREAT|O_EXCL|0755);
    if(ret == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    int write_fd = open(write_fifo, O_WRONLY);
    if(write_fd == -1)
    {
        perror("open write fifo");
        exit(1);
    }

    int read_fd;
    while((read_fd = open(read_fifo, O_RDONLY)) == -1)
    {
        sleep(1);
    }

    
    char sendbuf[256];
    char recvbuf[256];
    while(1)
    {
        printf("Ser:>");
        scanf("%s",sendbuf);
        write(write_fd, sendbuf, strlen(sendbuf)+1);
        read(read_fd, recvbuf, 256);
        printf("Cli:>%s\n",recvbuf);
    }

    close(write_fd);
    close(read_fd);
    return 0;
}







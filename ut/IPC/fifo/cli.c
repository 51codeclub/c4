
/**********************************************************
 *    > File Name: ser.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年10月27日 星期五 21时19分47秒
 **********************************************************/
#include"utili.h"

void send_msg(int fd)
{
    char buffer[256];
    while(1)
    {
        printf("Cli:>");
        scanf("%s",buffer);
        if(!strcmp(buffer,"quit"))
            break;
        write(fd, buffer, strlen(buffer)+1);
    }
}
void recv_msg(int fd)
{
    char buffer[256];
    while(1)
    {
        read(fd, buffer, 256);
        printf("Ser:>%s\n",buffer);
    }
}

int main()
{
    int read_fd = open(write_fifo, O_RDONLY);
    if(read_fd == -1)
    {
        perror("open read fifo");
        exit(1);
    }

    int ret;
    if((ret=access(read_fifo, F_OK) == -1))
    {
        ret = mkfifo(read_fifo, O_CREAT|O_EXCL|0755);
        if(ret == -1)
        {
            perror("mkfifo");
            close(read_fd);
            exit(1);
        }
    }
    int write_fd = open(read_fifo, O_WRONLY);
    if(write_fd == -1)
    {
        perror("open write fiof");
        exit(1);
    }

    pid_t pid = fork();
    if(pid == 0)
    {
        send_msg(write_fd);
    }
    else if(pid > 0)
    {
        recv_msg(read_fd);
        int status;
        wait(&status);
        close(write_fd);
        close(read_fd);
        unlink(read_fifo);
    }
    else
    {}

    return 0;
}








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
        printf("Ser:>");
        scanf("%s",buffer);
        if(!strcmp(buffer, "quit"))
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
        printf("Cli:%s\n",buffer);
    }
}

int main()
{
    int ret;
    if((ret=access(write_fifo, F_OK)) == -1)
    {
        ret = mkfifo(write_fifo, O_CREAT|O_EXCL|0755);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(1);
        }
    }

    printf("1111111111111111\n");
    int write_fd = open(write_fifo, O_WRONLY|O_NONBLOCK);
    if(write_fd == -1)
    {
        perror("open write fifo");
        exit(1);
    }
    printf("222222222222\n");

    int read_fd;
    while((read_fd = open(read_fifo, O_RDONLY)) == -1)
    {
        sleep(1);
    }


    pid_t pid = fork();
    if(pid == 0)
    {
        //child send msg
        send_msg(write_fd);
    }
    else if(pid > 0)
    {
        //parent recv msg
        recv_msg(read_fd);
        int status;
        wait(&status);
        close(write_fd);
        close(read_fd);
        unlink(write_fifo);
    }
    else
    {
        perror("fork.");
    }

    return 0;
}







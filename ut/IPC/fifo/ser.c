
/**********************************************************
 *    > File Name: ser.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
<<<<<<< HEAD
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
=======
 *    > Created Time: 2017年10月21日 星期六 11时01分43秒
 **********************************************************/

#include"utili.h"
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

int main()
{
    int ret;
<<<<<<< HEAD
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

=======
    if((ret=access(write_fifo, F_OK) != 0))
    {
        ret = mkfifo(write_fifo, O_CREAT|0755);
        if(ret == -1)
        {
            perror("mkfifo.");
            exit(1);
        }
    }
    printf("111111111111111\n");
    int write_fd = open(write_fifo, O_WRONLY|O_NONBLOCK);
    if(write_fd == -1)
    {
        perror("open write_fd.");
        exit(1);
    }
    printf("222222222222222\n");

    int read_fd;
    while( (read_fd = open(read_fifo, O_RDONLY)) == -1)
    {
        printf("Client is not start up.\n");
        sleep(1);
    }

    char send_buf[256];
    char recv_buf[256];
    while(1)
    {
        printf("Ser:>");
        scanf("%s",send_buf);
        write(write_fd, send_buf, strlen(send_buf)+1);
        read(read_fd, recv_buf, 256);
        printf("Cli:>%s\n",recv_buf);
    }

    close(write_fd);
    close(read_fd);

>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45
    return 0;
}






<<<<<<< HEAD
=======

>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

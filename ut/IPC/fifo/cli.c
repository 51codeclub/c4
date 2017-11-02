
/**********************************************************
<<<<<<< HEAD
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
=======
 *    > File Name: cli.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年10月21日 星期六 11时12分16秒
 **********************************************************/

#include"utili.h"
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

int main()
{
    int read_fd = open(write_fifo, O_RDONLY);
    if(read_fd == -1)
    {
<<<<<<< HEAD
        perror("open read fifo");
=======
        perror("open write_fd");
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45
        exit(1);
    }

    int ret;
<<<<<<< HEAD
    if((ret=access(read_fifo, F_OK) == -1))
    {
        ret = mkfifo(read_fifo, O_CREAT|O_EXCL|0755);
=======
    if((ret=access(read_fifo, F_OK))!= 0)
    {
        ret = mkfifo(read_fifo, O_CREAT|0755);
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45
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
<<<<<<< HEAD
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
=======
        perror("open read_fifo");
        close(read_fd);
        exit(1);
    }

    char send_buf[256];
    char recv_buf[256];
    while(1)
    {
        read(read_fd, recv_buf, 256);
        printf("Ser:>%s\n",recv_buf);
        printf("Cli:>");
        scanf("%s",send_buf);
        write(write_fd, send_buf, strlen(send_buf)+1);
    }

    close(write_fd);
    close(read_fd);

>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

    return 0;
}






<<<<<<< HEAD
=======


>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

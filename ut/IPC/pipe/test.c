
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月27日 星期五 21时03分55秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int fd[2]; //
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe");
        exit(1);
    }
    int fd1[2];
    ret = pipe(fd1);
    if(ret == -1)
    {
        perror("pipe1");
        exit(1);
    }
    pid_t pid = fork();
    if(pid == 0)
    {
        char *msg = "Yes. Sir.";
        char buf[100];
        close(fd[1]);
        close(fd1[0]);
        int nbyte = read(fd[0], buf, 100);
        printf("nbyte = %d\n",nbyte);
        printf("form parent msg:> %s\n",buf);
        write(fd1[1], msg, strlen(msg)+1);
        close(fd[0]);
        close(fd1[1]);
    }
    else if(pid > 0)
    {
        char buf[100];
        char *msg = "GoodGoodStudy, DayDayUp.";
        close(fd[0]);
        close(fd1[1]);
        write(fd[1], msg, strlen(msg)+1);
        read(fd1[0], buf, 100);
        printf("form child msg:>%s\n",buf);
        close(fd[1]);
        close(fd1[0]);
        int status;
        wait(&status);
    }
    else
    {
    }
    return 0;
}

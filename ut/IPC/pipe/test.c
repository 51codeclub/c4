
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
<<<<<<< HEAD
*    > Created Time: 2017年10月27日 星期五 21时03分55秒
=======
*    > Created Time: 2017年10月21日 星期六 09时40分01秒
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45
**********************************************************/

#include<stdio.h>
#include<unistd.h>
<<<<<<< HEAD
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
=======
#include"../../log.h"
#include<stdlib.h>

int main()
{
    char *parent_talk[] = {"Hello", "Can you tell me current time?","Oh MyGod, i have go.ByeBye",NULL};
    char *child_talk[] = {"Hi","No Problem.","GoodBye.",NULL};

    int fd1[2];
    int fd2[2];

    int ret = pipe(fd1);
    if(ret == -1)
    {
        sys_log(LOG_ERR,__FILE__,__LINE__,"Create pipe1 Fail.");
        exit(1);
    }
    ret = pipe(fd2);
    if(ret == -1)
    {
        sys_log(LOG_ERR,__FILE__,__LINE__,"Create pipe2 Fail.");
        exit(1);
    }

    pid_t pid = fork();
    if(pid == 0)
    {
        int i = 0;
        char buffer[256];
        close(fd1[1]);
        close(fd2[0]);
        char *child = child_talk[i];
        while(child != NULL)
        {
            read(fd1[0], buffer, 256);
            printf("Parent:> %s\n", buffer);
            if(i == 1)
            {
                time_t te;
                time(&te);
                memset(buffer, 0, 256);
                sprintf(buffer, "%s %s",child, ctime(&te));
                write(fd2[1], buffer, strlen(buffer)+1);
            }
            else
            {
                write(fd2[1], child, strlen(child)+1);
            }
            ++i;
            child = child_talk[i];
        }

        close(fd1[0]);
        close(fd2[1]);
    }
    else if(pid > 0)
    {
        int i = 0;
        int buffer[256];
        close(fd1[0]); //write
        close(fd2[1]); //read

        char *parent = parent_talk[i];
        while(parent != NULL)
        {
            write(fd1[1], parent, strlen(parent)+1);
            read(fd2[0], buffer, 256);
            printf("Child:> %s\n",buffer);

            ++i;
            parent = parent_talk[i];
        }

        close(fd1[1]);
        close(fd2[0]);

        int status;
        wait(&status);
    }
    else
    {
        perror("fork.");
    }

    return 0;
}

/*
int main()
{
    pid_t pid;
    
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        sys_log(LOG_ERR,__FILE__,__LINE__,"Create pipe fail.");
        exit(1);
    }
    else
    {
        sys_log(LOG_INFO, __FILE__, __LINE__, "Create pipe Success.");
    }
    
    pid = fork();

    if(pid == 0)
    {
        close(fd[1]);

        char buffer[256];
        read(fd[0], buffer, 256);
        printf("Form Parent Process msg:> %s\n", buffer);
        close(fd[0]);
    }
    else if(pid > 0)
    {
        char *msg = "GoodGoodStudy, DayDayUp.";
        close(fd[0]);
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);

>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45
        int status;
        wait(&status);
    }
    else
    {
<<<<<<< HEAD
    }
    return 0;
}
=======
        perror("fork.");
    }

    return 0;
}
*/
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

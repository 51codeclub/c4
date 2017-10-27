
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月18日 星期三 19时08分17秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    pid = fork();

    fork();
    fork();

    if(pid == 0)
    {
        printf("Child Sleep.......\n");
        printf("Child ppid = %d\n",getppid());
        sleep(3);
        printf("Child WakeUp, ppid = %d\n",getppid());
    }
    else if(pid > 0)
    {
        printf("Parent.\n");
        //sleep(4);
        int status;
        wait(&status);
        //waitpid();
        printf("Parent finish.\n");

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
    int i = 0;
    for(; i<2; ++i)
    {
        fork();
    }
    return 0;
}

/*
int main()
{
    pid_t pid;
    pid = fork();

    fork();
    fork();

    if(pid == 0)
    {
        printf("Child.pid=%d, ppid = %d\n",getpid(),getppid());
    }
    else if(pid > 0)
    {
        printf("Parent. pid = %d, ppid = %d\n",getpid(), getppid());
    }
    else
    {
        perror("fork");
    }

    sleep(1);
    return 0;
}

/*
int main()
{
    pid_t pid = 0;

    pid = fork();

    switch(pid)
    {
    case -1:
        perror("fork");
        break;
    case 0:
        printf("This is Child Process. pid = %d, ppid = %d\n", getpid(),getppid());
        break;
    default:
        printf("This is Parent Process.pid = %d, ppid = %d\n\n",getpid(),getppid());
        break;
    }

    return 0;
}

/*
void fun()
{
    printf("in fun pid = %d\n",getpid());
}
int main()
{
    printf("pid = %d\n",getpid());
    fun();
    return 0;
}

/*
int main()
{
    printf("pid = %d\n",getpid());
    printf("ppid = %d\n",getppid());
    printf("uid = %d\n", getuid());
    printf("euid = %d\n",geteuid());
    printf("gid = %d\n",getgid());
    printf("egid = %d\n",getegid());
    while(1)
    {
        sleep(1);
    }
    return 0;
}

/*
int main()
{
    int i = 0;
    while(1)
    {
        printf("i = %d\n", i++);
        sleep(1);
    }
    return 0;
}
*/

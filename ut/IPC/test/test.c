
/**********************************************************
 *    > File Name: test.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年10月27日 星期五 18时44分53秒
 **********************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>

//myshell

int main()
{
    printf("in test pid = %d, ppid = %d\n",getpid(),getppid());

    execl("tt","tt",NULL);
    printf("================\n");
    return 0;
}

/*
int main(int argc, char *argv[], char **env)
{
    //execl("/bin/ls","ls","-al",NULL);
    //execl("/bin/ls","ls",NULL);
    //execlp("ls","ls",NULL);  //PATH
    //exevle();

    char *arg[] = {"ls","-al",NULL};
    execv("/bin/ls", arg);
    return 0;
}

/*
int main()
{
    int i = 0;
    for(;;)
    {
        vfork();
        printf("i = %d\n",++i);
    }
    return 0;
}

/*
int main()
{
    int i = 0;

    pid_t pid = vfork();
    if(pid == 0)
    {
        i = 10;
        printf("in child : i = %d\n",i);
        exit(0);
    }
    else if(pid > 0)
    {
        printf("in parent : i = %d\n",i);
        int status;
        wait(&status);
    }

    return 0;
}

/*
int main()
{
    int i=0;
    for(;i<3; ++i)
    {
        vfork();
    }
    printf("pid = %d\n",getpid());
    //return 0;
    exit(0);
}

/*
static pid_t g_pid;

int main()
{
    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        pid = fork();
        if(pid == 0)
        {
            g_pid = getpid();
            printf("1 pid = %d\n",getpid());
        }
        else if(pid > 0)
        {
            printf("2 pid = %d\n",getpid());
            sleep(3);
        }
    }
    else if(pid > 0)
    {
        pid = fork();
        if(pid == 0)
        {
            printf("3 pid = %d\n",getpid());
            sleep(5);
        }
        else if(pid > 0)
        {
            sleep(1);
            int status;
            //pidret = wait(&status);
            printf("in parent pid = %d\n",g_pid);
            pid_t ret = waitpid(g_pid, &status, WUNTRACED);
            printf("ret pid = %d\n",ret);
        }
    }
    else
    {
        perror("fork");
    }

    printf("%d process finish.\n",getpid());
    return 0;
}


/*
int main()
{
    pid_t pid = fork();

    fork();
    if(pid == 0)
    {
        printf("child pid = %d\n",getpid());
        sleep(3);
        printf("child wake up.\n");
    }
    else if(pid > 0)
    {
        int status;
        printf("parent wait......\n");
        sleep(1);
        kill(pid, SIGKILL);
        pid_t pid_ret = wait(&status);
        printf("pid ret = %d\n",pid_ret);
        int ret = WIFEXITED(status);
        if(ret == 0)
        {
            printf("child is Error finish.\n");
        }
        else
        {
            printf("Child is OK finish.\n");
        }
    }
    return 0;
}
*/

/**********************************************************
*    > File Name: gettop.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月18日 星期一 20时53分06秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>

//getopt()
//optarg
//optopt
//optind
//opterr

int main(int argc, char *argv[])
{
    int ret;
    while((ret = getopt(argc, argv, ":myn:x::")) != -1)
    {
        switch(ret)
        {
        case 'm':
            printf("my name is baosongshan.\n");
            break;
        case 'y':
            printf("your name is 51codeclub.\n");
            break;
        case '?':
            break;
        }
    }
    return 0;
}

/*
//argument count
//argument value
int main(int argc, char *argv[])
{
    printf("argc = %d\n",argc);
    int i;
    for(i=0; i<argc; ++i)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
    }
    return 0;
}
*/

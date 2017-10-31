
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月31日 星期二 20时31分16秒
**********************************************************/


#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<stdlib.h>

int main()
{
    key_t key = ftok("mytest", 0xff);
    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }
    printf("key = %x\n",key);

    key = ftok("youtest", 0xff);
    if(key == -1)
    {
        perror("ftok 1");
        exit(1);
    }
    printf("key = %x\n",key);

    key = ftok("mytest", 0xfe);
    if(key == -1)
    {
        perror("ftok 2");
        exit(1);
    }
    printf("key = %x\n",key);

    key = ftok("mytest", 0x12ff);
    printf("key = %x\n",key);
    key = ftok("mytest", 0x23f1);
    printf("key = %x\n",key);

    return 0;
}







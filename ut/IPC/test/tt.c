
/**********************************************************
*    > File Name: tt.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月27日 星期五 20时44分16秒
**********************************************************/
#include<stdio.h>

int main()
{
    printf("in tt pid = %d, ppid = %d\n",getpid(), getppid());
    printf("I am tt.\n");

    return 0;
}

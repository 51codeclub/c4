
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月17日 星期二 18时49分55秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include"max.h"
#include"min.h"

int main()
{
    int a = 10;
    int b = 20;

    printf("max value = %d\n",max(a, b));
    printf("min vlaue = %d\n",min(a, b));
    return 0;
}


/**********************************************************
*    > File Name: main.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月18日 星期一 20时06分40秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>

#include"max.h"
#include"min.h"

int main()
{
    int a = 10;
    int b = 20;

    printf("max value = %d\n",Max(a,b));
    printf("min value = %d\n",Min(a,b));
    return 0;
}

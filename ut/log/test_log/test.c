
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月11日 星期三 20时12分17秒
**********************************************************/

#include"utili.h"
#include"log.h"
#include"myfunlib.h"

int main()
{
    FILE *fp = fopen("test.txt", "r");
    if(fp == NULL)
    {
        sys_log(LOG_ERR, __FILE__, __LINE__,"Open %s file error.", "test.txt");
        return -1;
    }

    fclose(fp);
    return 0;
}

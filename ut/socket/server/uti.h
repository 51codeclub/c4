#ifndef _UTI_H
#define _UTI_H
/**********************************************************
*    > File Name: utili.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月25日 星期六 19时39分43秒
**********************************************************/
#include<stdio.h>
#include<unistd.h>

typedef enum {QUIT, ADD, SUB, MUL, DIV, MOD}OP_ENUM;
#define CMD_SIZE 10

typedef struct opst
{
    int op1;
    int op2;
    OP_ENUM op;
}opst;

#endif // _UTILI_H

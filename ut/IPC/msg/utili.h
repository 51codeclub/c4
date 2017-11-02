#ifndef _UTILI_H
#define _UTILI_H
/**********************************************************
*    > File Name: utili.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月01日 星期三 21时18分00秒
**********************************************************/

#define SER_SND_FLG 100
#define SER_RCV_FLG 200
#define CLI_SND_FLG 200
#define CLI_RCV_FLG 100

#define MSG_BUFFER_SIZE 256

typedef struct Msg
{
    long msg_type;
    char msg_text[MSG_BUFFER_SIZE];
}Msg;

#endif // _UTILI_H


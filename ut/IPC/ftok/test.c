
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
<<<<<<< HEAD
*    > Created Time: 2017年10月31日 星期二 20时31分16秒
**********************************************************/


=======
*    > Created Time: 2017年10月27日 星期五 15时22分22秒
**********************************************************/

>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<stdlib.h>

int main()
{
    key_t key = ftok("mytest", 0xff);
    if(key == -1)
    {
<<<<<<< HEAD
        perror("ftok");
        exit(1);
    }
    printf("key = %x\n",key);
=======
        perror("fotk");
        exit(1);
    }
    else 
    {
        printf("key = %x\n",key);
    }

>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

    key = ftok("youtest", 0xff);
    if(key == -1)
    {
<<<<<<< HEAD
        perror("ftok 1");
        exit(1);
    }
    printf("key = %x\n",key);
=======
        perror("ftok1");
        exit(1);
    }
    else
        printf("key = %x\n",key);
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

    key = ftok("mytest", 0xfe);
    if(key == -1)
    {
<<<<<<< HEAD
        perror("ftok 2");
        exit(1);
    }
    printf("key = %x\n",key);

    key = ftok("mytest", 0x12ff);
    printf("key = %x\n",key);
    key = ftok("mytest", 0x23f1);
=======
        perror("ftok2");
        exit(1);
    }
    else
        printf("key = %x\n",key);

    key = ftok("mytest",0xff);
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45
    printf("key = %x\n",key);

    return 0;
}
<<<<<<< HEAD






=======
>>>>>>> 229499b18f85666d82d7a0e146a311c454873a45

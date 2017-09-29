
/**********************************************************
*    > File Name: convertcomment.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 16时57分04秒
**********************************************************/

#include"convertcomment.h"
#include"utili.h"

typedef enum

{

	NO_COMMENT_STATE,
	C_COMMENT_STATE,
	CPP_COMMENT_STATE,
	STR_STATE,
	END_COMMENT_STATE
}ENUM_STATE;



typedef  struct  STATA_MACHINE

{

	FILE  *InPutFile;
	FILE  *OutPutFile;
	ENUM_STATE state;
}StateMachine;



StateMachine   g_state;





void EventPro(char ch);



void Event_COMMENT_AT_NO(char ch);
void Event_COMMENT_AT_C(char ch);
void Event_COMMENT_AT_CPP(char ch);
void Event_COMMENT_AT_END(char ch);
void Event_COMMENT_AT_STR(char ch);
int convertcomment(FILE *inputfile, FILE *outputfile)
{
    if(inputfile==NULL || outputfile==NULL)
    {
        printf("argument is invalid.\n");
        return -1;
    }
	 g_state.InPutFile = inputfile;
	g_state.OutPutFile = outputfile:
	g_state.state = NO_COMMENT_STATE;



	char ch;



	while(g_state.state != END_COMMENT_STATE)
	{
		ch = fgetc(g_state.InPutFile);
		EventPro(ch);
	}
    	return 0;
}
void EventPro(char ch)
{
	switch(g_state.state)
	{
	case NO_COMMENT_STATE:
		Event_COMMENT_AT_NO(ch);

		break;
	case C_COMMENT_STATE:
		Event_COMMENT_AT_C(ch);

		break;
	case CPP_COMMENT_STATE:
		Event_COMMENT_AT_CPP(ch);
		break;
	case END_COMMENT_STATE:
		break;
	case STR_STATE:
		Event_COMMENT_AT_STR(ch);
		break;

	}


}



void Event_COMMENT_AT_NO(char ch)
{
	char NextRead;
	switch(ch)
	{
	case '/':
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/')           /*进入C++注释*/
			{
				fputc('/',g_state.OutPutFile);	
				fputc('*',g_state.OutPutFile);
				g_state.state = CPP_COMMENT_STATE;
			}
			else  if(  NextRead == '*')        /*进入C语言注释*/
			{
				fputc(ch,g_state.OutPutFile);
				fputc(NextRead,g_state.OutPutFile);
				g_state.state = C_COMMENT_STATE;
			}

			else                              
			{
				fputc(ch,g_state.OutPutFile);
				fputc(NextRead,g_state.OutPutFile);
				g_state.state = NO_COMMENT_STATE;

			}
		}
		break;

	case '"':                 /*进入字符串状态*/
		{
			fputc(ch,g_state.OutPutFile);
			g_state.state = STR_STATE;

		}
		break;
	case EOF:                         /*进入文件结尾*/
		g_state.state = END_COMMENT_STATE;

	case'\'':
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '"')
			{
				fputc(ch,g_state.OutPutFile);
				fputc(NextRead,g_state.OutPutFile);
			}
			else
			{
				fputc(ch,g_state.OutPutFile);
				fseek(g_state.InPutFile,-1,1); 
			}
		}
		break;

	default :
		fputc(ch,g_state.OutPutFile);
		break;
	}
}


/*c注释状态：可能遇到：c注释结束--》终态 c注释（空格代替），c++注释（空格代替），字符串状态（中的注释不改变）*/
void Event_COMMENT_AT_C(char ch)
{
	char NextRead;
	switch(ch)
	{
	case '*':                                                   /*c注释状态*/
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/')               /*c语言注释结束*/
			{
				fputc(ch,g_state.OutPutFile);
				fputc(NextRead,g_state.OutPutFile);
				g_state.state = NO_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g_state.OutPutFile);     /*只有一个星号将其打印*/
				fseek(g_state.InPutFile,-1,1);    /*因为求NextReaad时调用了fgetc，文件指针后移了一位，所以要将文件指针前移一味，否则会跳过一个字符*/

			}	
		}
		break;
	case '/': 
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/' || NextRead == '*')    /*参杂c++或者c语言注释，用两个空格代替*/
			{
				fputc( ' ',g_state.OutPutFile);
				fputc( ' ',g_state.OutPutFile);
			}
			else
			{
				fputc(ch,g_state.OutPutFile);     /*只有一个星号将其打印*/
				fseek(g_state.InPutFile,-1,1);    /*因为求NextReaad时调用了fgetc，文件指针后移了一位，所以要将文件指针前移一味，否则会跳过一个字符*/
			}


		}
		break;
	case '"':
		{
			fputc(ch,g_state.OutPutFile);
			g_state.state = STR_STATE;

		}
		break;


	default :
		fputc(ch,g_state.OutPutFile);
		break;
	}

}

/*          */
/*                                                                  */


/*C++注释状态：可能遇到：c++注释结束、c注释（空格代替）、c++注释（空格代替）、字符串状态（全部输出）*/
void Event_COMMENT_AT_CPP(char ch)
{
	char NextRead;

	switch(ch)
	{
	case '/':                                   /*C++中嵌套其他注释用两个空格代替                       */
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/')                    /*c++注释中嵌套c++注释用空格代替*/
			{

				fputc(' ',g_state.OutPutFile);
				fputc(' ',g_state.OutPutFile);
			}

			else  if(NextRead == '*')                /*进入c语言注释*/
			{
				fputc(' ',g_state.OutPutFile);
				fputc(' ',g_state.OutPutFile);

			}
			else 

			{
				fputc(ch,g_state.OutPutFile);     /*只有一个星号将其打印*/
				fseek(g_state.InPutFile,-1,1);    /*因为求NextReaad时调用了fgetc，文件指针后移了一位，所以要将文件指针前移一味，否则会跳过一个字符*/
			}

		}

		break;
	case '*':
		{

			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/')                    /*c++注释中嵌套c注释用空格代替*/
			{
				fputc(' ',g_state.OutPutFile);
				fputc(' ',g_state.OutPutFile);
			}

			else 

			{
				fputc(ch,g_state.OutPutFile);     /*只有一个星号将其打印*/
				fseek(g_state.InPutFile,-1,1);    /*因为求NextReaad时调用了fgetc，文件指针后移了一位，所以要将文件指针前移一味，否则会跳过一个字符*/
			}


		}
		break;
	case '\n':
		{
			fputc('*',g_state.OutPutFile);
			fputc('/',g_state.OutPutFile);
			fputc('\n',g_state.OutPutFile);
			g_state.state = NO_COMMENT_STATE;

		}
		break;



	default :
		fputc(ch,g_state.OutPutFile);
		break;
	}
}



void Event_COMMENT_AT_STR(char ch)

{
	char NextRead;
	switch(ch)
	{
	case '\0':
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '"')
			{
				fputc(ch,g_state.OutPutFile);
				fputc(NextRead,g_state.OutPutFile);
				g_state.state = NO_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g_state.OutPutFile);     /*只有一个星号将其打印*/
				fseek(g_state.InPutFile,-1,1);    /*因为求NextReaad时调用了fgetc，文件指针后移了一位，所以要将文件指针前移一味，否则会跳过一个字符*/
			}

		}	
		break;
	case'"':
		fputc(ch,g_state.OutPutFile);
		g_state.state = NO_COMMENT_STATE;

		break;
	case EOF:
		g_state.state = END_COMMENT_STATE;
		break;

	default :
		fputc(ch,g_state.OutPutFile);
		break;

	}

}

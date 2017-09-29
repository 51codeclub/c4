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

int ConvertComment(FILE *inputfile, FILE *outputfile)
{
	if(inputfile==NULL || outputfile==NULL)
	{
		cout<<"Invalid Argument."<<endl;
		return -1;
	}

	g_state.InPutFile = inputfile;
	g_state.OutPutFile = outputfile;
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
			if(NextRead == '/')           /*����C++ע��*/
			{
				fputc('/',g_state.OutPutFile);
				fputc('*',g_state.OutPutFile);
				g_state.state = CPP_COMMENT_STATE;
			}
			else  if(  NextRead == '*')        /*����C����ע��*/
			{
				fputc(ch,g_state.OutPutFile);
				fputc(NextRead,g_state.OutPutFile);
				g_state.state = C_COMMENT_STATE;
			}

			else                              
			{
				fputc(ch,g_state.OutPutFil;
				fputc(NextRead,g_state.OutPutFile);
				g_state.state = NO_COMMENT_STATE;

			}
		}
		break;

	case '"':                 /*�����ַ���״̬*/
		{
			fputc(ch,g_state.OutPutFile);
			g_state.state = STR_STATE;

		}
		break;
	case EOF:                    
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


/*cע��״̬������������cע�ͽ���--����̬ cע�ͣ��ո���棩��c++ע�ͣ��ո���棩���ַ���״̬���е�ע�Ͳ��ı䣩*/
void Event_COMMENT_AT_C(char ch)
{
	char NextRead;
	switch(ch)
	{
	case '*':                                                   /*cע��״̬*/
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/')               /*c����ע�ͽ���*/
			{
				fputc(ch,g_state.OutPutFile);
				fputc(NextRead,g_state.OutPutFile);
				g_state.state = NO_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g_state.OutPutFile);     /*ֻ��һ���ǺŽ����ӡ*/
				fseek(g_state.InPutFile,-1,1);    /*��Ϊ��NextReaadʱ������fgetc���ļ�ָ�������һλ������Ҫ���ļ�ָ��ǰ��һζ�����������һ���ַ�*/

			}	
		}
		break;
	case '/': 
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/' || NextRead == '*')    /*����c++����c����ע�ͣ��������ո����*/
			{
				fputc( ' ',g_state.OutPutFile);
				fputc( ' ',g_state.OutPutFile);
			}
			else
			{
				fputc(ch,g_state.OutPutFile);     /*ֻ��һ���ǺŽ����ӡ*/
				fseek(g_state.InPutFile,-1,1);    /*��Ϊ��NextReaadʱ������fgetc���ļ�ָ�������һλ������Ҫ���ļ�ָ��ǰ��һζ�����������һ���ַ�*/
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


/*C++ע��״̬������������c++ע�ͽ�����cע�ͣ��ո���棩��c++ע�ͣ��ո���棩���ַ���״̬��ȫ�������*/
void Event_COMMENT_AT_CPP(char ch)
{
	char NextRead;

	switch(ch)
	{
	case '/':                                   /*C++��Ƕ������ע���������ո����                       */
		{
			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/')                    /*c++ע����Ƕ��c++ע���ÿո����*/
			{

				fputc(' ',g_state.OutPutFile);
				fputc(' ',g_state.OutPutFile);
			}

			else  if(NextRead == '*')                /*����c����ע��*/
			{
				fputc(' ',g_state.OutPutFile);
				fputc(' ',g_state.OutPutFile);

			}
			else 

			{
				fputc(ch,g_state.OutPutFile);     /*ֻ��һ���ǺŽ����ӡ*/
				fseek(g_state.InPutFile,-1,1);    /*��Ϊ��NextReaadʱ������fgetc���ļ�ָ�������һλ������Ҫ���ļ�ָ��ǰ��һζ�����������һ���ַ�*/
			}

		}

		break;
	case '*':
		{

			NextRead = fgetc(g_state.InPutFile);
			if(NextRead == '/')                    /*c++ע����Ƕ��cע���ÿո����*/
			{
				fputc(' ',g_state.OutPutFile);
				fputc(' ',g_state.OutPutFile);
			}

			else 

			{
				fputc(ch,g_state.OutPutFile);     /*ֻ��һ���ǺŽ����ӡ*/
				fseek(g_state.InPutFile,-1,1);    /*��Ϊ��NextReaadʱ������fgetc���ļ�ָ�������һλ������Ҫ���ļ�ָ��ǰ��һζ�����������һ���ַ�*/
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
				fputc(ch,g_state.OutPutFile);     /*ֻ��һ���ǺŽ����ӡ*/
				fseek(g_state.InPutFile,-1,1);    /*��Ϊ��NextReaadʱ������fgetc���ļ�ָ�������һλ������Ҫ���ļ�ָ��ǰ��һζ�����������һ���ַ�*/
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

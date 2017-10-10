
/**********************************************************
*    > File Name: convertcomment.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 16时57分04秒
**********************************************************/

#include"convertcomment.h"

//定义状态
typedef enum
{
    NO_COMMENT_STATE,
    C_COMMENT_STATE,
    CPP_COMMENT_STATE,
  //  STRING_STATE,
    END_STATE
}enum_state;

//定义状态机
typedef struct 
{
    FILE *inputfile;
    FILE *outputfile;
    enum_state ulstate;
}state_machine;

/////////////////////////////////////////////////////
FILE* open_file(char *filename, char *mode)
{
    FILE *fp = fopen(filename, mode);
    if(NULL == fp)
    {
        printf("open %s fail.\n",filename);
        exit(1);
    }
    return fp;
}
void close_file(FILE *fp)
{
    fclose(fp);
}

char read_ch(FILE *fp)
{
    assert(NULL != fp);
    return fgetc(fp);
}
void write_ch(char ch, FILE *fp)
{
    assert(NULL != fp);
    fputc(ch, fp);
}
void write_double_ch(char ch1, char ch2, FILE *fp)
{
    assert(NULL != fp);
    fputc(ch1, fp);
    fputc(ch2, fp);
}

/////////////////////////////////////////////////////
state_machine g_state;

int convertcomment(FILE *inputfile, FILE *outputfile)
{
    if(NULL == inputfile || NULL == outputfile)
    {
        printf("argument is invalid.\n");
        return -1;
    }

    //初始化状态机
    g_state.inputfile = inputfile;
    g_state.outputfile = outputfile;
    g_state.ulstate = NO_COMMENT_STATE; 

    char ch;
    while(END_STATE != g_state.ulstate)
    {
        ch = read_ch(g_state.inputfile);
        eventpro(ch);
    }
    
    return 0;
}

void eventpro(char ch)
{
    switch(g_state.ulstate)
    {
    case NO_COMMENT_STATE:
        eventpro_no(ch);
        break;
    case C_COMMENT_STATE:
        eventpro_c(ch);
        break;
    case CPP_COMMENT_STATE:
        eventpro_cpp(ch);
        break;
  /*  case STRING_STATE:
        eventpro_str(ch);
        break;*/
    }
}

void eventpro_no(char ch)
{
    char nextch;
    switch(ch)
    {
    case '/':
        nextch = read_ch(g_state.inputfile);
        if('/' == nextch)   //C++ Comment
        {
            write_double_ch('/','*', g_state.outputfile);
            g_state.ulstate = CPP_COMMENT_STATE;
        }
        else if('*' == nextch)   //C Comment
        {
            write_double_ch('/','*', g_state.outputfile);
            g_state.ulstate = C_COMMENT_STATE;
        }
        else
        {
            write_double_ch('/',nextch,g_state.outputfile);
        }
        break;
    case '"':
        eventpro_str(ch);
        break;
    case EOF:
        g_state.ulstate = END_STATE;
        break;
    default:
        write_ch(ch, g_state.outputfile);
        break;
    }
}
void eventpro_c(char ch)
{
    char nextch;
    switch(ch)
    {
    case '/':
        nextch = read_ch(g_state.inputfile);
        if('/' == nextch || '*' == nextch)   //C++ Comment
        {
            write_double_ch(' ', ' ', g_state.outputfile);
        }
        else
        {
            write_double_ch('/', nextch, g_state.outputfile);
        }
        break;
    case '*':
        nextch = read_ch(g_state.inputfile);
        if('/' == nextch)   
        {
            write_double_ch('*', '/', g_state.outputfile);
            g_state.ulstate = NO_COMMENT_STATE;
        }
        else
        {
            write_double_ch('*', nextch, g_state.outputfile);
        }
        break;
    case '"':
        eventpro_str(ch);
        break;
    case EOF:
        g_state.ulstate = END_STATE;
        break;
    default:  
            write_ch(ch, g_state.outputfile);
        break;
    }
}
void eventpro_cpp(char ch)
{
    char nextch;
    switch(ch)
    {
    case '\n':
        write_double_ch('*', '/', g_state.outputfile);
        fputc('\n',g_state.outputfile);
        g_state.ulstate = NO_COMMENT_STATE;
        break;
    case '/':
        nextch = read_ch(g_state.inputfile);
        if('/' == nextch || '*' == nextch)
        {
            write_double_ch(' ', ' ', g_state.outputfile);
        }
        else
        {
            write_double_ch('/', nextch, g_state.outputfile);
        }
        break;
    case '*':
        nextch = fgetc(g_state.inputfile);
        if('/' == nextch)
        {
            write_double_ch(' ', ' ', g_state.outputfile);
        }
        else
        {
            write_double_ch('*', nextch, g_state.outputfile);
        }
        break;
    case '"':
        eventpro_str(ch);
        break;
    case EOF:
        write_double_ch('*', '/', g_state.outputfile);
        g_state.ulstate = END_STATE;
        break;
    default:
        write_ch(ch, g_state.outputfile);
        break;
    }
}
void eventpro_str(char ch)
{
    char nextch;
    int flag = 1;
    int mark = 1;
    long n = 0;
    write_ch('"', g_state.outputfile);
    nextch = read_ch(g_state.inputfile);
    while(EOF != nextch && mark && flag)
    {
        if('"' == nextch)
        {
            flag = 0;
        }
        else if('\n' == nextch)
        {
            mark = 0;
        }
        else
        {
            nextch = read_ch(g_state.inputfile);
            n++;
        }
    }
    if(1 == flag && 1 == mark)         //EOF case
    {
        fseek(g_state.inputfile, -n+1, 1);
        nextch = read_ch(g_state.inputfile);
        while(EOF != nextch)
        {
            write_ch(nextch, g_state.outputfile);
            nextch = read_ch(g_state.inputfile);
        }
    }
    else if(1 == flag && 0 == mark)         //'\n'case
    {
        fseek(g_state.inputfile, -n-1, 1);
        nextch = read_ch(g_state.inputfile);
        while('\n' != nextch)
        {
            write_ch(nextch, g_state.outputfile);
            nextch = read_ch(g_state.inputfile);
        }
    }
    else
    {
        fseek(g_state.inputfile, -n, 1);  //'"' case
        nextch = read_ch(g_state.inputfile);
        while('"' != nextch)
        {
            write_ch(nextch, g_state.outputfile);
            nextch = read_ch(g_state.inputfile);
        }
        write_ch('"', g_state.outputfile);
    }
}

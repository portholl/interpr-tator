#include "scanner.hpp"

char* Name_lex::Scanner:: TW [ ] = 
{"","and","begin","bool","do","else","end",// 1 2 3 4 5 6
"if","false","int","not","or","program","read",// 7 8 9 10 11 12 13
"then","true","var","while","write", NULL }; // 14 15 16 17 18 

char* Name_lex::Scanner:: TD [ ] = 
{"", "@",";", ",", ":", ":=", "(", ")",// 1 2 3 4 5 6 7
"=","<", ">", "+", "-", "*", "/", "<=", "!=", ">=", NULL};// 8 9 10 11 12 13 14 15 16 17

type_of_lex Name_lex::Scanner::words[] = {LEX_NULL,LEX_AND,LEX_BEGIN, LEX_BOOL,LEX_DO,LEX_ELSE,LEX_END,LEX_IF,
LEX_FALSE,LEX_INT,LEX_NOT,LEX_OR,LEX_PROGRAM,LEX_READ,LEX_THEN,LEX_TRUE,LEX_VAR,LEX_WHILE,LEX_WRITE,LEX_NULL };

type_of_lex Name_lex::Scanner::dlms[] = {LEX_NULL,LEX_FIN,LEX_SEMICOLON,LEX_COMMA,LEX_COLON,LEX_ASSIGN,LEX_LPAREN,LEX_RPAREN,
LEX_EQ,LEX_LSS,LEX_GTR,LEX_PLUS,LEX_MINUS,LEX_TIMES,LEX_SLASH,LEX_LEQ,LEX_NEQ,LEX_GEQ,LEX_NULL}; 

void Name_lex::Scanner::clear()
{
    buf_top = 0;
    for (int j = 0; j < 80; ++j) //усли изменился размкр buf поменять
        buf[j] = '\0';
}
void Name_lex::Scanner::add()
{
    buf[buf_top++] = c; 
}
int Name_lex::Scanner::look(const char * buf, char **list)
{ 
    int i = 0;
    while (list[i]) 
    {  
        if ( std::string(buf) == std::string(list[i]) )
            return i; 
        i++; 
    }
    return 0; 
}
 void Name_lex::Scanner::gc()
 {
    
    c = fgetc(fp);
    //std::cout<<c<<std::endl;
 }
 Name_lex::Lex Name_lex::Scanner::get_lex()
{
    int d, j;
    CS = H;
    do
    {   
        switch(CS)
        {
            case H:
                if ( c==' ' || c == '\n' || c== '\r' || c == '\t' ) 
                    gc();
                else if ( isalpha(c) ) //eсли буква
                {
                    clear();
                    add();
                    gc();
                    CS = IDENT;
                }
                else if ( isdigit(c) )
                {
                    d = c - '0';
                    gc();
                    CS = NUMB;
                }
                else if ( c== '{' )
                {
                    gc();
                    CS = COM;
                }
                else if ( c== ':' || c== '<' || c== '>' )
                { 
                    clear(); 
                    add(); 
                    gc(); 
                    CS = ALE; 
                }
                else if (c == '@')
                    { //std::cout<< "|" << buf << "|"<<std::endl;
                    return Lex(LEX_FIN);}
                else if (c == '!')
                {
                    clear();
                    add();
                    gc();
                    CS = NEQ;
                }
                else 
                    CS = DELIM;
                break;
            case IDENT:
                if ( isalpha(c) || isdigit(c) ) 
                {
                    add(); 
                    gc();
                }
                else if ( j = look (buf, TW) )
                {   //std::cout<< "|" << buf<<"|"<<std::endl;
                    return Lex (words[j], j); }
                else
                {
                    j = TID.put(buf);
                    //std::cout<< "|" << buf << "|"<<std::endl;
                    return Lex (LEX_ID, j);
                }
                break;
            case NUMB:
                if (isdigit(c)) 
                {
                    d = d * 10 + (c - '0'); 
                    gc();
                }
                else
                    {
                     //std::cout<< "|" << buf<<"|"<<std::endl;
                    return Lex (LEX_NUM, d);
                    }
                break;
            case COM:
                if ( c == '}' )
                {
                    gc();
                    CS = H;
                }
                else if (c == '@' || c == '{' )
                    throw c;
                else
                    gc();
                break;
            case ALE:
                if ( c == '=')
                {
                    add();
                    gc();
                    j = look (buf, TD);
                    // std::cout<< "|" << buf<<"|"<<std::endl;
                    return Lex (dlms[j], j);
                }
                else
                {
                    j = look (buf, TD);
                    // std::cout<< "|" << buf<<"|"<<std::endl;
                    return Lex (dlms[j], j);
                }
                break;
            case NEQ:
                if (c == '=')
                {
                    add();
                    gc();
                    j = look (buf, TD);
                    //std::cout<< "|" << buf<<"|"<<std::endl;
                    return Lex (LEX_NEQ, j);
                }
                else
                    throw '!';
                break;
            case DELIM:
                clear();
                add();
                if ( j = look ( buf, TD) )
                {
                    gc();
                    // std::cout<< "|" << buf<<"|"<<std::endl;
                    return Lex ( dlms[j], j );
                }
                else
                    throw c;
            break;
        }//end switch
    } while (true);
}
 Name_lex::Scanner::Scanner(const char *program)
{
    fp = fopen (program, "r"); 
    CS = H;
    clear();
    gc();
}

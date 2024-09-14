#include "parcer.hpp"
void Name_lex::Parser::P()
{
    if (c_type == LEX_PROGRAM)
        gl();
    else
        throw curr_lex;
    D1();
    // for (int i =0 ; i< 5; i++)//////////////////сколлько переменных
    // {
    //     std::cout<< TID[i].get_name() <<" "<< TID[i].get_value()<<" "<< TID[i].get_declare() <<std::endl ;
    // }
    if (c_type == LEX_SEMICOLON)
        gl();
    else
        throw curr_lex;
    B();
    if (c_type != LEX_FIN)
        throw curr_lex;
}
void Name_lex::Parser::D1()
{
    if (c_type == LEX_VAR)
    {
        gl();
        D();
        while (c_type == LEX_COMMA) //,
        {
            gl();
            D();
        }
    }
    else
        throw curr_lex;
}
void Name_lex::Parser::D()
{
    st_int.reset(); //top = 0
    if (c_type != LEX_ID) //смотрим объявление в var
        throw curr_lex;
    else
    {
        st_int.push (c_val);
        gl();
        while (c_type == LEX_COMMA)//,
        {
            gl();
            if (c_type != LEX_ID)
                throw curr_lex;
            else
            {
                st_int.push (c_val); //в stack
                gl();
            }
        }
        if (c_type != LEX_COLON)//двоеточие =
            throw curr_lex;
        else
        {
            gl();
            if (c_type == LEX_INT)
            {   
                dec ( LEX_INT );
                gl();
            }
            else if (c_type == LEX_BOOL)
            {
                dec ( LEX_BOOL );
                gl();
            }
            else  throw curr_lex;
        }
    }
}
void Name_lex::Parser::B()
{
    if (c_type == LEX_BEGIN)
    {
        gl();
        S();
        while (c_type == LEX_SEMICOLON) //;
        {
            gl();
            S();
        }
        if (c_type == LEX_FIN)//!!!!!!!!1
            gl();
        else
            { std::cout<<"2"<<std::endl; throw curr_lex;}
    }
    else
        { std::cout<<"3"<<std::endl; throw curr_lex;}
}
void Name_lex::Parser::S()
    {
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_IF)
    {
        gl();
        E();
        eq_bool();
        pl2 = prog.get_free (); //prog - полиз
        prog.blank();
        prog.put_lex (Lex(POLIZ_FGO));
        if (c_type == LEX_THEN)
        {
            gl();
            S();
            // if (curr_lex.get_type() != LEX_SEMICOLON)
            //      throw curr_lex;
            // gl();
            //if (curr_lex.get_type() != LEX_SEMICOLON) gl();//////////
            pl3 = prog.get_free();
            prog.blank();
            prog.put_lex (Lex(POLIZ_GO));
            prog.put_lex (Lex(POLIZ_LABEL, prog.get_free()), pl2);
            if (c_type == LEX_ELSE)
            {
                gl();
                S();
                prog.put_lex (Lex(POLIZ_LABEL, prog.get_free()), pl3);
            }
            else
                {std::cout<<"7"<<std::endl; throw curr_lex;}
        }
        else
            throw curr_lex;
    }//end if
    else if (c_type == LEX_WHILE)
    {
        pl0=prog.get_free();
        gl();
        E();
        eq_bool();
        pl1=prog.get_free(); 
        prog.blank();
        prog.put_lex (Lex(POLIZ_FGO));
        if (c_type == LEX_DO)
        {
            gl();
            S();
            prog.put_lex (Lex (POLIZ_LABEL, pl0));
            prog.put_lex (Lex ( POLIZ_GO));
            prog.put_lex (Lex ( POLIZ_LABEL, prog.get_free()), pl1);
            if (c_type == LEX_END) { c_type = LEX_FIN;}///
        }
        else
            { std::cout<<"1"<<std::endl; throw curr_lex;}
    }//end while
    else if (c_type == LEX_READ) //////////////////////////// перепроверить
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            if (c_type == LEX_ID) {
                check_id_in_read();
                prog.put_lex (Lex ( POLIZ_ADDRESS, c_val) );
                gl();
            }
            else
                throw curr_lex;
            if ( c_type == LEX_RPAREN )
            {
                gl();
                prog.put_lex (Lex (LEX_READ));
            }
            else
                throw curr_lex;
        }
    else
        throw curr_lex;
    }//end read
    else if (c_type == LEX_WRITE)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            E();
            if (c_type == LEX_RPAREN)
            {
                gl();
                prog.put_lex (Lex(LEX_WRITE));
            }
            else
                throw curr_lex;
        }
        else
            { std::cout<<"8"<<std::endl; throw curr_lex;}
    }//end write
    else if ( c_type == LEX_ID )
    {
        check_id ();
        prog.put_lex (Lex (POLIZ_ADDRESS, c_val) );
        ///////////////////TID[i].put_value();
        gl();
        if ( c_type == LEX_ASSIGN ) //=
        {
            gl();
            E();
            eq_type();
            prog.put_lex (Lex (LEX_ASSIGN) );
        }
        else
            throw curr_lex;
    }//assign-end
    else if (c_type == LEX_END)//
        { 
            c_type = LEX_FIN;
        }
    else
        {B();}
}
void Name_lex::Parser::E()
{
    E1();
    if ( c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
        c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ )
    {
        st_lex.push (c_type);
        type_of_lex op = c_type;
        gl(); 
        E1(); 
        check_op();
        prog.put_lex(op); 
    }
}
void Name_lex::Parser::E1() 
{
    T();
    while ( c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR)
    {
        st_lex.push (c_type);
        type_of_lex op = c_type;
        gl();
        T();
        check_op();
        prog.put_lex(op); 
    }
}
void Name_lex::Parser::T ()
{
    F();
    while ( c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND)
    {
        st_lex.push (c_type);
        type_of_lex op = c_type;
        gl();
        F();
        check_op();
        prog.put_lex(op); 
    }
}
void Name_lex::Parser::F()
{
    if ( c_type == LEX_ID ) 
    {
        check_id();
        prog.put_lex (Lex (LEX_ID, c_val));
        gl();
    }
    else if ( c_type == LEX_NUM ) 
    {
        st_lex.push ( LEX_INT );
        prog.put_lex ( curr_lex );
        gl();
    }
    else if ( c_type == LEX_TRUE ) 
    {
        st_lex.push ( LEX_BOOL );
        prog.put_lex (Lex (LEX_TRUE, 1) );
        gl();
    }
    else if ( c_type == LEX_FALSE)
    {
        st_lex.push ( LEX_BOOL );
        prog.put_lex (Lex (LEX_FALSE, 0) );
        gl();
    }
    else if (c_type == LEX_NOT) 
    {
        gl(); 
        F(); 
        check_not();
    }
    else if ( c_type == LEX_LPAREN ) //?????????????????????????
    {
        gl(); 
        E();
        if ( c_type == LEX_RPAREN)
            gl();
        else 
            throw curr_lex;
    }
    else 
        throw curr_lex;
}
void Name_lex::Parser::dec(type_of_lex type)
{
  int i;
  while ( !st_int.is_empty()) 
  {
    i = st_int.pop();
    if (TID[i].get_declare()) 
      throw "twice";
    else 
    {
      TID[i].put_declare();
      TID[i].put_type(type);
      TID[i].put_assign();///////////
    }
  }
}
void Name_lex::Parser::check_id()
{   //std::cout << TID[c_val].get_declare() <<" "<< c_val<< std::endl;
    if ( TID[c_val].get_declare() )
        st_lex.push ( TID[c_val].get_type() );
    else 
        throw "not declared";
}
void Name_lex::Parser::check_op()
{
    type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;
    
    t2 = st_lex.pop();
    op = st_lex.pop();
    t1 = st_lex.pop();
    if (op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH)
        r = LEX_INT;
    if (op == LEX_OR || op == LEX_AND)
        t = LEX_BOOL;
    if (t1 == t2  &&  t1 == t) 
        st_lex.push(r);
    else
        throw "wrong types are in operation";
    //prog.put_lex (Lex(op) );/////
}
void Name_lex::Parser::check_not()
{
    if (st_lex.pop() != LEX_BOOL)
        throw "wrong type is in not";
    else 
    {
        st_lex.push (LEX_BOOL);
        prog.put_lex (Lex (LEX_NOT));
    }
}
void Name_lex::Parser::eq_type()
{
    if (st_lex.pop() != st_lex.pop())
        throw "wrong types are in :=";
}
void Name_lex::Parser::eq_bool()
{
    if ( st_lex.pop() != LEX_BOOL )
        throw "expression is not boolean";
}
void Name_lex::Parser::check_id_in_read()
{
    if ( !TID [c_val].get_declare() )
        throw "not declared";
}
void Name_lex::Parser::gl()
{
    curr_lex = scan.get_lex();
    c_type = curr_lex.get_type();
    c_val = curr_lex.get_value();
}
void Name_lex::Parser::analyze()
{
    gl();
    P();
    prog.print();
    std::cout<<std::endl<<"Yes!!!"<<std::endl;
}
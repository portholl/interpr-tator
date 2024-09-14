#ifndef _parcer_H
#define _parcer_H
#include "lex.hpp"
#include "scanner.hpp"
#include "stack.hpp"
#include "poliz.hpp"
//#include "tabl_ident.hpp"
namespace Name_lex
{   extern Name_lex::tabl_ident TID;
    class Parser 
    {
        Lex curr_lex;
        type_of_lex c_type;
        int c_val;
        Scanner scan;
        Stack <int, 100> st_int;
        Stack <type_of_lex, 100>  st_lex;
        void P();
        void D1();
        void D();
        void B();
        void S();
        void E();
        void E1();
        void T();
        void F();
        void dec (type_of_lex type);
        void check_id ();
        void check_op ();
        void check_not ();
        void eq_type ();
        void eq_bool ();
        void check_id_in_read ();
        void gl ();
    public:
        Poliz prog;
        Parser (const char *program) : scan (program), prog (1000) {}
        void analyze();
    };
}
#endif //_parcer_H
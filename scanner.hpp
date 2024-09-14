#ifndef _scanner_H
#define _scanner_H
#include <fstream> 
#include "lex.hpp"
#include "const.hpp"
#include "tabl_ident.hpp"
namespace Name_lex{
    extern Name_lex::tabl_ident TID;
    class Scanner 
    {

        enum state { H, IDENT, NUMB, COM, ALE, DELIM, NEQ };
        static char * TW[];
        static type_of_lex words[];
        static char * TD[];
        static type_of_lex dlms[];
        state CS;
        FILE * fp; 
        char c;
        char buf[80];
        int buf_top;
        void clear ();
        void add ();
        int look (const char *buf, char **list);
        void gc ();
    public:
        Lex get_lex ();
        Scanner (const char * program);
        ////////////////


    };
}

#endif //_scanner_H
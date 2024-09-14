#ifndef _poliz_H
#define _poliz_H
#include "lex.hpp"
#include "tabl_ident.hpp"
extern Name_lex::tabl_ident TID;
namespace Name_lex
{
    class Poliz
    {
        Lex* p;
        int size;
        int free;
    public:
        Poliz (int max_size);
        ~Poliz();
        void put_lex (Lex l);
        void put_lex (Lex l, int place);
        void blank();
        int get_free ();
        Lex & operator[] (int index);
        void print ();
    };
}
#endif// _poliz_H
#ifndef _tabl_ident_H
#define _tabl_ident_H
#include "ident.hpp"
namespace Name_lex
{
    class tabl_ident
    {
        ident * p;
        int size;
        int top;
    public:
        tabl_ident (int max_size);
        ~tabl_ident ();
        ident& operator[] (int k);
        int put (const std::string buf);
    };
}
#endif //_tabl_ident_H
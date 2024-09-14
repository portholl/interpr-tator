#include "tabl_ident.hpp"
namespace Name_lex {Name_lex::tabl_ident TID(100); };
Name_lex::tabl_ident::tabl_ident(int max_size)
{
    p = new ident[size=max_size];
    top = 1;
}
Name_lex::tabl_ident::~tabl_ident()
{
    delete []p;
}
Name_lex::ident &Name_lex::tabl_ident::operator[](int k)
{
    return p[k];
}
int Name_lex::tabl_ident::put(const std::string buf)
{
    for ( int j = 1; j < top; j++ )
        if (buf == p[j].get_name()) 
            return j;
    p[top].put_name(buf);
    ++top;
    return top-1;
}
#include "poliz.hpp"
Name_lex::Poliz::Poliz(int max_size)
{
    p = new Lex[size = max_size];
    free = 0;
}
Name_lex::Poliz::~Poliz() { delete [] p; }
void Name_lex::Poliz::put_lex(Name_lex::Lex l)
{
    p[free] = l;
    free++;
}
void Name_lex::Poliz::put_lex(Name_lex::Lex l, int place) 
{ 
    p[place] = l; 
}
void Name_lex::Poliz::blank() 
{
    ++free;
}
int Name_lex::Poliz::get_free()
{
    return free;
}
Name_lex::Lex & Name_lex::Poliz::operator[](int index)
{
    if (index > size)
        throw "POLIZ:out of array";
    else if (index > free)
        throw "POLIZ:indefinite element of array";
    else
        return p[index];
}
void Name_lex::Poliz::print()
{
    for ( int i = 0; i < free; ++i )
        std::cout << p[i];
}
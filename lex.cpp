#include "lex.hpp"
type_of_lex Name_lex::Lex::get_type() const 
{ 
    return t_lex; 
}
int Name_lex::Lex::get_value() const 
{ 
    return v_lex; 
}
std::ostream &Name_lex::operator<<(std::ostream &s, Name_lex::Lex l){
    s << '(' << l.t_lex << ',' << l.v_lex << ");" ;
    return s;
}
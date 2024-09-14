#include "ident.hpp"
Name_lex::ident::ident()
{
    declare = false; 
    assign = false; 
}
Name_lex::ident::ident(const std::string n)
{
    name = n; 
    declare = false; 
    assign = false; 
    std::cout<<name;
}
bool Name_lex::ident::operator==(const std::string&s) const
{
    return name == s; 
}
std::string Name_lex::ident::get_name() const 
{
    return name;
}
void Name_lex::ident::put_name(const std::string n)
{   
    name = n; //strcpy(name, n);
}
bool Name_lex::ident::get_declare() const 
{   
    return declare; 
}
void Name_lex::ident::put_declare()
{
    declare = true; 
}
type_of_lex Name_lex::ident::get_type() const 
{
     return type; 
}
void Name_lex::ident::put_type(type_of_lex t)
{  
    type = t; 
}
bool Name_lex::ident::get_assign() const 
{
    return assign;
}
void Name_lex::ident::put_assign() { assign = true;}
int Name_lex::ident::get_value() const { return value; }
void  Name_lex::ident::put_value (int v) { value = v; }


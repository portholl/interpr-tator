#ifndef _ident_H
#define _ident_H
#include <iostream>
#include <string>
#include "lex.hpp"
#include <stdio.h>
#include "const.hpp"
namespace Name_lex{
    class ident {
        std::string name; //char *
        bool declare;
        type_of_lex type;
        bool assign;
        int value;
    public:
        ident (); 
        ident (const std::string);
        bool operator== (const std::string& s) const ;
        std::string get_name ()const ; // char * 
        void put_name (const std::string n);
        bool get_declare ()const ;
        void put_declare ();
        type_of_lex get_type ()const ;
        void put_type (type_of_lex t);
        bool get_assign ()const ;
        void put_assign ();
        int get_value ()const ;
        void put_value (int v);
};

}
#endif //_ident_H
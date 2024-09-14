#ifndef _executer_H
#define _executer_H
#include "lex.hpp"
#include "poliz.hpp"
#include "stack.hpp"
#include "const.hpp"
#include "tabl_ident.hpp"
#include "scanner.hpp"

namespace Name_lex
{   extern Name_lex::tabl_ident TID;
    class Executer
    {
        Lex pc_el;
        
    public:
        void execute (Poliz & prog);
    };
}
#endif// _executer_H
#ifndef interpritaror_H
#define interpritaror_H
#include "parcer.hpp"
#include "executer.hpp"
//#include "tabl_ident.hpp"
//extern Name_lex::tabl_ident TID;
namespace Name_lex
{
    class Interpretator
    {
        Parser pars;
        Executer E;
    public:
        Interpretator(char* program): pars(program) {}
        void interpretation ();
    };

}
#endif //interpritaror_H
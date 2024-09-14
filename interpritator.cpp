#include "interpritator.hpp"
void Name_lex::Interpretator::interpretation()
{
    pars.analyze();
    E.execute(pars.prog);
}
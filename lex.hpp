#ifndef _N_lex
#define  _N_lex
#include <iostream>
#include "const.hpp"
namespace Name_lex{
 // namespace Name_lex
class Lex {
    type_of_lex t_lex;
    int v_lex;
public:
    Lex (type_of_lex t = LEX_NULL, int v = 0) : t_lex (t), v_lex(v){};
    type_of_lex get_type() const;
    int get_value () const;
    friend std::ostream& operator << (std::ostream & s, Lex l );
};
}
#endif //_N_lex
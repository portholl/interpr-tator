#include <iostream>
#include "interpritator.hpp"
#include "lex.hpp"
#include "const.hpp"
using namespace std;
int main ()
{   
    try
    {
        Name_lex::Interpretator I("prog4.txt");
        I.interpretation();
        return 0;
    }
    catch (char c)
    {
        cout<<"unexpected symbol "<<c<<endl;
        return 1;
    }
    catch (Name_lex::Lex l)
    {
        cout<<"unexpected lexeme";
        cout<<l << endl;
        return 1;
    }
    catch (const char *source)
    {
        cout<<source<<endl;
        return 1;
    }
} 
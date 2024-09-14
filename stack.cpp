#include "stack.hpp"
template<class T, int max_size> 
Name_lex::Stack<T, max_size>::Stack()
{
    top = 0;
}
template<class T, int max_size> 
void Name_lex::Stack<T, max_size>::reset()
{
    top = 0;
}
template<class T, int max_size> 
void Name_lex::Stack<T, max_size>::push(T i)
{
    if ( !is_full() )
        s[top++] = i;
  else
    throw "Stack_is_full";
}
template<class T, int max_size> 
T Name_lex::Stack<T, max_size>::pop()
{
    if (!is_empty())
        return s[--top]; //?? почему не top--
    else
        throw "Stack_is_empty";
}
template<class T, int max_size> 
bool Name_lex::Stack<T, max_size>::is_empty()
{
    return top == 0;
}
template<class T, int max_size> 
bool Name_lex::Stack<T, max_size>::is_full()
{
    return top = max_size;
}
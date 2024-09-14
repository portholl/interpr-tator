#ifndef _stack_H
#define _stack_H
namespace Name_lex
{
    template < class T, int max_size >
    class Stack
    {
        T s [max_size];
        int top;
    public:
        Stack() {top = 0; } ;
        void reset(){top = 0;};
        void push(T i)
        {
            if ( !is_full() )
                s[top++] = i;
            else throw "Stack_is_full";
        };
        T pop()
        {
            if (!is_empty())
                return s[--top]; //?? почему не top--
            else throw "Stack_is_empty";
        };
        bool is_empty(){ return top == 0;};
        bool is_full(){return top == max_size;};
    };
}
#endif //_stack_H
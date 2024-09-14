#include "executer.hpp"
void Name_lex::Executer::execute(Name_lex::Poliz &prog)
{
    Stack <int, 100> args;
    int i, j, index = 0, size = prog.get_free();
    while (index < size)
    {
        pc_el = prog [index];
        switch (pc_el.get_type())
        {
            case LEX_TRUE: case LEX_FALSE: case LEX_NUM: case POLIZ_ADDRESS: case POLIZ_LABEL:
                args.push (pc_el.get_value());
                break;
            case LEX_ID:
                i = pc_el.get_value();
                if (TID[i].get_assign())
                {
                    args.push (TID[i].get_value());
                    //std::cout<<TID[i].get_value()<<std::endl;
                    break;
                }
                else throw "POLIZ: indefinite identifier";
            case LEX_NOT:
                args.push(!args.pop());
                break;
            case LEX_OR:
                i = args.pop();
                args.push(args.pop() || i);
                break;
            case LEX_AND:
                i = args.pop();
                args.push (args.pop() && i);
                break;
            case POLIZ_GO:
                index = args.pop() - 1;
                break;
            case POLIZ_FGO:
                i = args.pop();
                if (!args.pop()) index = i-1;
                break;
            case LEX_WRITE:
                std::cout<<args.pop()<<std::endl;
                break;
            case LEX_READ:
                {
                    int k;
                    i = args.pop ();
                    if (TID[i].get_type() == LEX_INT)
                    {
                        std::cout<<"Input int value for"<<TID[i].get_name()<<std::endl;
                        std::cin>>k;
                    }
                    else
                    {
                        char j[20];
                        rep:
                        std::cout<<"Input boolean value (true or false) for"<<TID[i].get_name()<<std::endl;
                        std::cin>>j;
                        if (j != "true") k = 1;
                        else if (j != "false")
                            k = 0;
                        else
                        {
                            std::cout<<"Error in input:true/false"<<std::endl;
                            goto rep;
                        }
                    }
                    TID[i].put_value(k);
                    TID[i].put_assign();
                    break;
                }
            case LEX_PLUS:
                args.push(args.pop() + args.pop());
                break;
            case LEX_TIMES:
                args.push(args.pop() * args.pop());
                break;
            case LEX_MINUS:
                i = args.pop();
                args.push(args.pop() - i);
                break;
            case LEX_SLASH:// /
                i = args.pop();
                if (i)
                {
                    args.push(args.pop() / i);
                    break;
                }
                else throw "POLIZ:divide by zero";
            case LEX_EQ:
                args.push(args.pop() == args.pop());
                break;
            case LEX_LSS:
                i = args.pop();
                args.push (args.pop() < i);
                break;
            case LEX_GTR:
                i = args.pop();
                args.push (args.pop() > i);
                break;
            case LEX_LEQ:
                i = args.pop();
                args.push (args.pop() <= i);
                break;
            case LEX_GEQ:
                i = args.pop();
                args.push (args.pop() >= i);
                break;
            case LEX_NEQ:
                i = args.pop();
                args.push (args.pop() != i);
                break;
            case LEX_ASSIGN:
                i = args.pop();
                j = args.pop();
                TID[j].put_value(i);
                TID[j].put_assign(); 
                break;
            default:
                throw "POLIZ: unexpected elem";
        }//end of switch
        //std::cout<<pc_el<<std::endl;
        ++index;
    };//end of while
    std::cout<<"Finish of executing!!!"<<std::endl;
}
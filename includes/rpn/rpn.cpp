#include "rpn.h"

RPN::RPN()
{
  
}
RPN::RPN(const Queue<Token*> &input_q)
{
    queue = input_q;
}
  
void RPN::set_input(const Queue<Token*> &input_q)
{
    queue = input_q;
}


double RPN::operator()(double value)
{
    return rpn(value);  
}

double RPN::rpn(double value)
{  
    Stack<Token*> stack;
    double y = -9999 ;              // if stack is not 1(supposed to be), return this number

    while (queue.size() > 0)
    {
        Token* item =  queue.pop();

        if(item->TokenType() == INTEGER)
        {
            stack.push(item);
        }
        else if(item->TokenType() == OPERATOR)
        {
            if(stack.size() < 2)
            {
                break;
            }
        
            double top = static_cast<Integer*>(stack.pop())->getNum();
            double bot = static_cast<Integer*>(stack.pop())->getNum();

            double result = static_cast<Operator*>(item)->evaluate(bot, top);
            stack.push(new Integer(result));
        }
        // else if(item->TokenType() == FUNCTION)
        // {
        //     stack.push(new Integer(value));
        // }

        else if(item->TokenType() == FUNCTION)
        {
            if(item->prec() == 10)      // prec == 10 (variable other than trig functions)
            {
                stack.push(new Integer(value));
            }

            else                        // trig functions -> pop and calculate
            {
                if(stack.size() < 1)
                {
                    break;
                }
        
                double x = static_cast<Integer*>(stack.pop())->getNum();
                double y = static_cast<Function*>(item)->evaluate(x);
                stack.push(new Integer(y));
            }
        }

        // cout << "STACK SIZE " << stack.size() << endl;
        // cout << "TOP OF STACK " << *stack.top() << endl;
        
  }

    // if(stack.size() == 0)
    //     cout << "stack is empty, cant compute rpn" << endl;
    //     return;
    // else if(stack.size() != 1)
    //     cout << "stack has more than 1 entry, messed up rpn!" <<endl;

    if(stack.size() == 1)
        y = static_cast<Integer*>(stack.pop())->getNum();
    return y;       // if rpn fails, return -9999
}
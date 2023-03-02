#include "shunting_yard.h"
  
ShuntingYard::ShuntingYard()
{

}

ShuntingYard::ShuntingYard(const Queue<Token*>& input_q)
{
    queue = input_q;
}

ShuntingYard::ShuntingYard(string input_q)
{
  // put string into queue of token
  Queue<Token*> infix;

  for(int i=0; i<input_q.length(); i++)
  {
    string num;

    // NUMBER & VAR
    if(input_q[i] <= '9' && input_q[i] >= '0')
    {
      // infix.push(new Integer(static_cast<double>(input_q[i] - '0')));
      while (input_q[i] <= '9' && input_q[i] >= '0' || i<=input_q.length() && input_q[i] == '.')
      {
        num += input_q[i++];
      }
      i--;
      infix.push(new Integer(stod(num)));
      num.clear();
    }
    else if(input_q[i] == 'x' || input_q[i] == 'X')
    {
      infix.push(new Function("X"));
    }
    // PARENs
    else if(input_q[i] == '(')
    {
      infix.push(new LeftParen());
    }
    else if(input_q[i] == ')')
    {
      infix.push(new RightParen());
    }
    // TRIG FUNC
    else if(input_q[i] == 's' && input_q[i+1] == 'i' && input_q[i+2] == 'n')
    {
        infix.push(new Function("sin"));
        i += 2;
    }
    else if(input_q[i] == 'c' && input_q[i+1] == 'o' && input_q[i+2] == 's')
    {
      infix.push(new Function("cos"));
      i += 2;
    }
    else if(input_q[i] == 'a' && input_q[i+1] == 'r' && input_q[i+2] == 'c' && input_q[i+3] == 's' && input_q[i+4] == 'i' && input_q[i+5] == 'n')
    {
      infix.push(new Function("asin"));
      i += 5;
    }
    else if(input_q[i] == 'a' && input_q[i+1] == 'r' && input_q[i+2] == 'c' && input_q[i+3] == 'c' && input_q[i+4] == 'o' && input_q[i+5] == 's')
    {
      infix.push(new Function("acos"));
      i += 5;
    }
    else if(input_q[i] == 'a' && input_q[i+1] == 'r' && input_q[i+2] == 'c' && input_q[i+3] == 't' && input_q[i+4] == 'a' && input_q[i+5] == 'n')
    {
      infix.push(new Function("atan"));
      i += 5;
    }
    else if(input_q[i] == 't' && input_q[i+1] == 'a' && input_q[i+2] == 'n')
    {
      infix.push(new Function("tan"));
      i += 2;
    }
    else if(input_q[i] == 'l' && input_q[i+1] == 'o' && input_q[i+2] == 'g')
    {
      infix.push(new Function("log"));
      i += 2;
    }
    else if(input_q[i] == 's' && input_q[i+1] == 'q' && input_q[i+2] == 'r' && input_q[i+3] == 't')
    {
      infix.push(new Function("sqrt"));
      i += 3;
    }
    // OPERATORS
    else if(input_q[i] == '+')
    {
      infix.push(new Operator("+"));
    }
    else if(input_q[i] == '-')
    {
      infix.push(new Operator("-"));
    }
    else if(input_q[i] == '*')
    {
      infix.push(new Operator("*"));
    }
    else if(input_q[i] == '/')
    {
      infix.push(new Operator("/"));
    }
    else if(input_q[i] == '^')
    {
      infix.push(new Operator("^"));
    }
  }
  queue = infix;
}


void ShuntingYard::infix(const Queue<Token*>& input_q)
{
    queue = input_q;
}
  

Queue<Token*> ShuntingYard::postfix()
{
    return shunting_yard();
}
 
Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& input_q)
{
    queue = input_q;
    return shunting_yard();
}

Queue<Token*> ShuntingYard::shunting_yard()
{
    Queue<Token*> postfix;
    Stack<Token*> stack;

    Queue<Token*>::Iterator it = queue.begin();
    while(it != queue.end())
    {
      Token* item = *it;
      if(item->TokenType() == INTEGER)
      {
        postfix.push(item);
      }
      else if(item->TokenType() == OPERATOR)
      {
        while(stack.size() != 0)
        {
            Token* item_on_stack = stack.top();
            if(item_on_stack->prec() >= item->prec() && item_on_stack->TokenType() != LPAREN)
            {
                postfix.push(stack.pop());
            }
            else
            {
              break;
            }
        }
        stack.push(item);
      }
      else if(item->TokenType() == LPAREN || item->TokenType() == FUNCTION)
      {
        stack.push(item);
      }
      else if(item->TokenType() == RPAREN)
      {
        while(stack.size() != 0)
        {
            Token* item_on_stack = stack.top();
            if(item_on_stack->TokenType() != LPAREN)
            {
                postfix.push(stack.pop());
            }
            else
            {
              stack.pop();
              break;
            }
        }
      }
      it++;
    }

    while(stack.size() > 0)
    {
      postfix.push(stack.pop());
    }
    
    return postfix;
}

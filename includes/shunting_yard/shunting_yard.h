#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

class ShuntingYard
{
public:
  ShuntingYard();
  ShuntingYard(const Queue<Token*>& input_q);
  ShuntingYard(string input_q);

  void infix(const Queue<Token*>& input_q);
  
  Queue<Token*> postfix();
  Queue<Token*> postfix(const Queue<Token*>& input_q);

  Queue<Token*> shunting_yard();
private:
  Queue<Token*> queue;
};

#endif 
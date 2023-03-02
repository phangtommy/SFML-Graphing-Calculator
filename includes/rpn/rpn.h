#ifndef RPN_H
#define RPN_H

#include <iostream>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

using namespace std;

class RPN
{
public:
  RPN();
  RPN(const Queue<Token*> &input_q);
  
  // set Q
  void set_input(const Queue<Token*> &input_q);

  // overloaded ()
  double operator()(double value = 0);
  double rpn(double value = 0);

private:
  Queue<Token*> queue;
};

#endif //RPN_H
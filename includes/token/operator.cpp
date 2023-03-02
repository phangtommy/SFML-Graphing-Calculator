#include "operator.h"

  Operator::Operator()
  {

  }
  
  Operator::Operator(string op)
  {
    _op = op;
    
    if(_op == "+" || _op == "-")
    {
      _precedence = 1;
    }
    else if (_op == "*" || _op == "/")
    {
      _precedence = 2;
    }
    else if(_op == "^")
    {
      _precedence = 3;
    }
  }

  void Operator::Print(ostream &outs) const
  {
    outs<<"["<<_op<<"]";
  }

   ostream& operator <<(ostream& outs, const Operator& op)
  {
    op.Print();
    return outs;
  }

  double Operator::evaluate(double a, double b)
  {
    double result;

    if(_op == "+")
    {
      return result = a + b;
    }
    else if (_op == "-")
    {
      return result = a - b;
    }
    else if (_op == "*")
    {
      return result = a * b;
    }
    else if(_op == "/")
    {
      return result = a / b;
    }
    else if(_op == "^")
    {
      return result = pow(a,b);
    }
    return -1;
  }
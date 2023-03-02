#ifndef OPERATOR_H
#define OPERATOR_H
#include "token.h"
#include "integer.h"
#include <cmath>
#include <cstring>

class Operator : public Token
{
public:
    Operator();
    Operator(string op);

    void Print(ostream &outs=cout) const;
    friend ostream& operator <<(ostream& outs, const Operator& op);

    TOKEN_TYPES TokenType(){return OPERATOR;}
    string op(){return _op;}
    int prec(){return _precedence;}
    
    double evaluate(double a, double b);

private:
    int _precedence;
    string _op;
}; 

#endif
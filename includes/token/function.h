#ifndef FUNCTION_H
#define FUNCTION_H
#include "token.h"
#include "integer.h"
#include "operator.h"
#include <string>

class Function : public Operator
{
public:
    Function();
    Function(string fx);

    void Print(ostream &outs=cout) const;
    friend ostream& operator <<(ostream& outs, const Function& fx);

    TOKEN_TYPES TokenType(){return FUNCTION;}
    string fx(){return _fx;}
    int prec(){return _precedence;}

    double evaluate(double x);
  
private:
    int _precedence;
    string _fx;
};

#endif
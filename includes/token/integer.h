#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include "token.h"
using namespace std;

class Integer : public Token
{
public:
    Integer();
    Integer(double value);
    Integer(string value);

    void Print(ostream &outs=cout) const ;
    TOKEN_TYPES TokenType(){return INTEGER;}
    double getNum(){return i;} //example of a function present in a child
private:
    double i;
};

#endif // INTEGER_H

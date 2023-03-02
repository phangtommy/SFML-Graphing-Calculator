#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include "token.h"

class RightParen : public Token
{
public:
    RightParen();
    RightParen(string arg);

    void Print(ostream &outs=cout) const;
    TOKEN_TYPES TokenType(){return RPAREN;}

private:
    string _rparen;
};

#endif
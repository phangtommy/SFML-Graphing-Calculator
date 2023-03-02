#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include "token.h"

class LeftParen : public Token
{
public:
    LeftParen();
    LeftParen(string arg);

    void Print(ostream &outs=cout) const;
    TOKEN_TYPES TokenType(){return LPAREN;}

private:
    string _lparen;
};


#endif
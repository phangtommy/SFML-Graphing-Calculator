#include "leftparen.h"

LeftParen::LeftParen()
{
    _lparen = "(";
}
LeftParen::LeftParen(string arg)
{
    _lparen = arg;
}

void LeftParen::Print(ostream &outs) const
{
    outs<<"["<<_lparen<<"]";
}
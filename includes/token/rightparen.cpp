#include "rightparen.h"

RightParen::RightParen()
{
    _rparen = ")";
}
RightParen::RightParen(string arg)
{
    _rparen = arg;
}

void RightParen::Print(ostream &outs) const
{
    outs<<"["<<_rparen<<"]";
}
#include "token.h"

Token::Token()
{
    
}

ostream& operator <<(ostream& outs, const Token& token)
{
    token.Print();
    return outs;
}

void Token::Print(ostream &outs) const
{
    outs<<"TOKEN Print: DON't ^%#$# call me again!"<<endl;
}

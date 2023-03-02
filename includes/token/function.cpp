#include "function.h"

Function::Function()
{

}
Function::Function(string fx)
{
    for(int i=0; i<fx.length(); i++)
    {
        fx[i] = toupper(fx[i]);
    }
    _fx = fx;
    _precedence = 10;
    if(_fx == "SIN" || _fx == "COS" || _fx == "TAN" || _fx == "ASIN" || _fx == "ACOS" || _fx == "ATAN" || _fx == "LOG" || _fx == "SQRT")
      _precedence = 9;
}

void Function::Print(ostream &outs) const
{
    outs<<"["<<_fx<<"]";
}

ostream& operator <<(ostream& outs, const Function& fx)
{
    fx.Print();
    return outs;
}

double Function::evaluate(double x)
{
    double result;

    if(_fx == "SIN")
    {
      return sin(x);
    }
    else if (_fx == "COS")
    {
      return cos(x);
    }
    else if (_fx == "TAN")
    {
      return tan(x);
    }
    else if(_fx == "ASIN")
    {
      return asin(x);
    }
    else if(_fx == "ACOS")
    {
      return acos(x);
    }
    else if(_fx == "ATAN")
    {
      return atan(x);
    }
    else if(_fx == "LOG")
    {
      return log(x);
    }
    else if(_fx == "SQRT")
    {
      return sqrt(x);
    }
    return -1;
}

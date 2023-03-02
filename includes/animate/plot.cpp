#include "plot.h"

Plot::Plot()
{

}

Plot::Plot(graph_info* info)
{
    _info = info;
}

void Plot::set_info(graph_info* info)
{
    _info = info;
}

// return vector of screen coordinates
Vector<sf::Vector2f> Plot::operator()()
{
    ShuntingYard input(_info->_equation);                    // take eq into shunting yard
    Queue<Token*> postfix = input.postfix();                  // put the result of shunting yard into q
    RPN rpn(postfix);                                         // set for calculation

    Vector<sf::Vector2f> SFML_points(_info->_points);             // make vector with size of given pts
    Coordinate_translator graph_to_screen(_info);                 // translate to SFML coordinate  
    for(double i=_info->_domain.x; i<=_info->_domain.y; i= i+_info->_delta)
    {
        rpn.set_input(postfix);                             // reset q (q will be empty for every calculation)
        double y = rpn(i);                                  // calculate y for each x interval

        // [TODO] Polar coordinate
        // double r = sqrt(pow(i,2)+pow(y,2));     
        // double theta = atan(y/i) ;      // in radians,  *180.0f/M_PI 
        // x = r*cos(theta)
        // y = r*sin(theta)
        // cout << "(x,y) is " << "(" << i << "," << y << "), "
        //     << "(r,theta) is " << "(" << r << ", " << theta  << ")" << endl;
        // SFML_points.push_back(graph_to_screen.translate(sf::Vector2f(r,theta)));      
                    
        SFML_points.push_back(graph_to_screen.translate(sf::Vector2f(i,y)));      // push the translated vector coordinate
    }
    return SFML_points;                                 // vector of screen coordinates
}
#ifndef PLOT_H
#define PLOT_H
#include "graph_info.h"
#include "coordinate_translator.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "../vector/vector_class.h"
// #include <cmath>

class Plot
{
public: 
    Plot();
    Plot(graph_info* info);
    
    void set_info(graph_info* info);
    Vector<sf::Vector2f> operator()();

private:
    graph_info* _info;
    Queue<Token*> postfix;
};

#endif // PLOT_H
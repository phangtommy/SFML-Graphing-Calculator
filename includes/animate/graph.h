#ifndef GRAPH_H
#define GRAPH_H
#include "graph_info.h"
#include "plot.h"
// #include "texthistory.h"

class Graph
{
public:
    Graph();
    Graph(graph_info* info);

    void set_info(graph_info* info);
    void update(graph_info* info);

    void draw(sf::RenderWindow& window);
    
private:
    graph_info* _info;
    Plot _plotter;
    Vector<sf::Vector2f> _points;
    
    sf::Font font;
	sf::Text label;
    sf::Text current_fx;     
    sf::Text _pressF;
    sf::Text _pressTab;
};

#endif  // GRAPH_H
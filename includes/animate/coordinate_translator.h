#ifndef COORDINATE_TRANSLATOR_H
#define COORDINATE_TRANSLATOR_H
#include "graph_info.h"

class Coordinate_translator
{
public:
    Coordinate_translator();
    Coordinate_translator(graph_info* info);

    sf::Vector2f translate(sf::Vector2f point);
    sf::Vector2f operator()(sf::Vector2f point);

private:
    graph_info* _info;
};

#endif // COORDINATE_TRANSLATOR_H
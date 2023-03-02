#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include "constant.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

struct graph_info
{
    string _equation;

    sf::Vector2f _window_dimension = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::Vector2f _origin = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    sf::Vector2f _offset = sf::Vector2f(0,0);
    sf::Vector2f _domain = sf::Vector2f(-8,8);
    sf::Vector2f _range = sf::Vector2f(-8,8);
    sf::Vector2f _scale = sf::Vector2f(_window_dimension.x / (_domain.y - _domain.x),
                                       _window_dimension.y / (_range.y - _range.x));
    int _points = 2022;       
    double _delta = (_domain.y - _domain.x) / _points;   
    
    bool _tab;
    bool _showCoor;
    bool _showGrid;
    bool _getInput;
};

#endif
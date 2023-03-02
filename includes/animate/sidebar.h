#ifndef SIDEBAR_H
#define SIDEBAR_H
#include "graph_info.h"
#include "texthistory.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow &window);

    void set_info(graph_info* info);
    void setEquation(string equation);
    void deleteEquation();
    void closefile();
    void mousePos(float x, float y);
    
private:
    sf::RectangleShape rect;            //sidebar rectangle
    sf::Font font;                      //used to draw text

    float _left;
    float _width;

    graph_info* _info;
    ifstream fin;
    Texthistory eq;                         // equations and the bounding box
    vector<Texthistory> texthistory;        // vector of the eq
    sf::Text _pressDel;
};

#endif // SIDEBAR_H

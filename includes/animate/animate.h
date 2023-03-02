#ifndef GAME_H
#define GAME_H
#include "graph_info.h"
#include "system.h"
#include "sidebar.h"
#include <SFML/Graphics.hpp>

class animate{
public:
    animate();

    void run();
    void processEvents();
    void update();
    void render();
    void Draw();

    // ~animate();
    // void set_info(graph_info* info);
private:
    graph_info* _info;
    
    sf::RenderWindow window;
    System system;                      //container for all the animated objects
    Sidebar sidebar;                    //rectangular message sidebar

    sf::CircleShape mousePoint;         //The little red dot
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text input_label;               //text to draw on main screen
    bool mouseIn;                       //mouse is in the screen

    string _input;
    string _output = "f(x) = ";     
    sf::Text _coorlabel;               // (x,y) of mouse label
    float mouseX, mouseY;              // (x,y) of mouse
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // GAME_H

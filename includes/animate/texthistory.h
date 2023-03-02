#ifndef TEXTHISTORY_H
#define TEXTHISTORY_H
#include "graph_info.h"
#include <vector>

class Texthistory
{
public:
    Texthistory(){};
    void draw(sf::RenderWindow& window);
    // Texthistory(sf::Font& font, string str, sf::Color color, sf::Vector2f pos = sf::Vector2f(0,0));

    sf::FloatRect getBounds();
    sf::String getEq();

    void set_eq(string str);
    void set_font(sf::Font& font);
    void set_color(sf::Color color);
    void set_pos(sf::Vector2f pos);
    void set_bold();

private:
    sf::Text text;
    // sf::Font font;
    sf::RectangleShape boundingbox;
};

#endif // TEXTHISTORY_H
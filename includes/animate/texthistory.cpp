#include "texthistory.h"

void Texthistory::draw(sf::RenderWindow &window)
{
    window.draw(text);
}

// Texthistory::Texthistory(sf::Font& font, string str, sf::Color color, sf::Vector2f pos) 
// {
//     // if (!font.loadFromFile("../arial.ttf")) //Roboto-Thin.ttf
//     // {
//     //     cout << "Sidebar() CTOR: Font failed to load" << endl;
//     //     cin.get();
//     //     exit(-1);
//     // }
//     text.setFont(font);
//     text.setString(str);
//     text.setFillColor(color);
//     text.setPosition(pos);
//     text.setCharacterSize(20);
//     boundingbox.setPosition(sf::Vector2f(text.getGlobalBounds().left-5, text.getGlobalBounds().top-5));
//     boundingbox.setSize(sf::Vector2f(text.getGlobalBounds().width+5, text.getGlobalBounds().height+5));
// }

sf::FloatRect Texthistory::getBounds()
{
    return boundingbox.getGlobalBounds();
}

sf::String Texthistory::getEq() 
{
    return text.getString();
}

void Texthistory::set_font(sf::Font& font)
{
    text.setFont(font);
}

void Texthistory::set_eq(string str)
{
    text.setString(str);
}

void Texthistory::set_color(sf::Color color) 
{
    text.setFillColor(color);
}

void Texthistory::set_pos(sf::Vector2f pos)
{
    text.setPosition(pos);
    text.setCharacterSize(20);
    boundingbox.setPosition(sf::Vector2f(text.getGlobalBounds().left-5, text.getGlobalBounds().top-5));
    boundingbox.setSize(sf::Vector2f(text.getGlobalBounds().width+5, text.getGlobalBounds().height+5));
}

void Texthistory::set_bold()
{
    if(text.getStyle())
        text.setStyle(sf::Text::Regular);
    else
        text.setStyle(sf::Text::Bold);
}
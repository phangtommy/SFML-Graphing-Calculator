#include "graph.h"

Graph::Graph()
{
    if (!font.loadFromFile("../Roboto-Thin.ttf"))
    {
        cout << "graph() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
}

/*
    graph CTOR, set_info, update:
        pass graph _info to _plotter to fill up _points vector
*/ 

Graph::Graph(graph_info* info)
{
    _info = info;
    _plotter.set_info(info);
}

void Graph::set_info(graph_info* info)
{
    _info = info;
    _plotter.set_info(info);
}

void Graph::update(graph_info* info)            
{
    _plotter.set_info(info);
    _points = _plotter();
}

void Graph::draw(sf::RenderWindow &window)      // draw x and y axis, & the vector points
{
    float size = 2;
    float radius = 2;
    float fontSize = 24;
    sf::Color fx_clr = sf::Color::Green;
    sf::Color x_axis_clr = sf::Color::Yellow;
    sf::Color y_axis_clr = sf::Color::Yellow;
    sf::Color x_grid_clr = sf::Color::Cyan;
    sf::Color y_grid_clr = sf::Color::Cyan;

    // Current displayed function
    current_fx = sf::Text(_info->_equation, font);
    current_fx.setCharacterSize(20);
    current_fx.setStyle(sf::Text::Bold);
    current_fx.setFillColor(sf::Color::Green);
    current_fx.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - current_fx.getLocalBounds().height - 10));

    // x-axis
    sf::RectangleShape x_axis(sf::Vector2f(_info->_window_dimension.x, size));  // width = entire screen, length = scaled
    x_axis.setFillColor(x_axis_clr);
    x_axis.setOrigin(sf::Vector2f(size/2,size/2));
    x_axis.setPosition(0, (_info->_origin.y + _info->_offset.y));
    window.draw(x_axis);

    // y-axis
    sf::RectangleShape y_axis(sf::Vector2f(size, _info->_window_dimension.y));  // width = scaled, length = entire screen
    y_axis.setFillColor(y_axis_clr);
    y_axis.setOrigin(sf::Vector2f(size/2,size/2));
    y_axis.setPosition((_info->_origin.x + _info->_offset.x), 0);
    window.draw(y_axis);

    // Toggle coordinates
    if(_info->_showCoor && _info->_scale.x > 15)
    {
        // x-coordinates
        for(int i=_info->_domain.x; i<_info->_domain.y; i++)
        {
            label = sf::Text(to_string(i), font);
            label.setCharacterSize(fontSize);
            label.setFillColor(x_axis.getFillColor());
            label.setPosition(sf::Vector2f(y_axis.getPosition().x + (i*_info->_scale.x) , x_axis.getPosition().y));
            window.draw(label);
        }
        // y-coordinates
        for(int i=_info->_range.y; i>=_info->_range.x; i--)
        {
            label = sf::Text(to_string(i), font);
            label.setCharacterSize(fontSize);
            label.setFillColor(y_axis.getFillColor());
            label.setPosition(sf::Vector2f(y_axis.getPosition().x  , x_axis.getPosition().y + (-i*_info->_scale.y) )); 
            window.draw(label);
        }
    }

    // Toggle grids
    if(_info->_showGrid)
    {
        // x-gridlines
        for(int i=_info->_range.y; i>=_info->_range.x; i--)
        {
            sf::RectangleShape x_grid(sf::Vector2f(_info->_window_dimension.x, 0.1));  
            x_grid.setFillColor(x_grid_clr);
            x_grid.setOrigin(sf::Vector2f(size/4,size/4));
            x_grid.setPosition(sf::Vector2f(0, x_axis.getPosition().y + (-i*_info->_scale.y) ));
            window.draw(x_grid);
        }
        // y-gridlines
        for(int i=_info->_domain.x; i<_info->_domain.y; i++)
        {
            sf::RectangleShape y_grid(sf::Vector2f(0.1, _info->_window_dimension.y)); 
            y_grid.setFillColor(y_grid_clr);
            y_grid.setOrigin(sf::Vector2f(size/4,size/4));
            y_grid.setPosition(sf::Vector2f(y_axis.getPosition().x + (i*_info->_scale.x), 0));
            window.draw(y_grid);
        }
    }

    // point coordinates of function
    sf::CircleShape circle(radius);
    circle.setFillColor(fx_clr);
    circle.setOrigin(circle.getRadius(),circle.getRadius());
    for(int i=1; i<_points.size(); i++)     // if i=0, uneven for x^2
    {
        circle.setPosition(_points[i].x, _points[i].y);           
        window.draw(circle);
    }

    // ☰ hamburger menu
    if(!_info->_tab)
    {
        // [TODO] Clickable menu
        // Texthistory tab(font, "[TAB]" , sf::Color::Yellow, sf::Vector2f(SCREEN_WIDTH - tab.getGlobalBounds().width - 55,10));
        // // tab.setBold();
        // tab.draw(window);

        // sf::FloatRect textBounds = tab.getGlobalBounds();
        // if (textBounds.contains(sf::Vector2f(x,y))) 
        // {
        //     tab.setFillColor(sf::Color::Green);
        // }
        // else 
        // {
        //     tab.setFillColor(sf::Color::Yellow);
        // }    

        _pressTab = sf::Text("[TAB]", font);
        _pressTab.setCharacterSize(20);
        _pressTab.setFillColor(sf::Color::Yellow);
        _pressTab.setPosition(sf::Vector2f(SCREEN_WIDTH - _pressTab.getLocalBounds().width - 15, 10));
        window.draw(_pressTab);
    }

    // [fx] menu
    if(!_info->_getInput)
    {
        // [TODO] Clickable menu
        // Texthistory fx(font, "[f]" , sf::Color::Yellow, sf::Vector2f(10,10));
        // fx.draw(window);
        
        _pressF = sf::Text("[f]", font);
        _pressF.setCharacterSize(20);
        _pressF.setFillColor(sf::Color::Yellow);
        _pressF.setPosition(sf::Vector2f(10,10));
        window.draw(_pressF);
    }

    window.draw(current_fx);
}


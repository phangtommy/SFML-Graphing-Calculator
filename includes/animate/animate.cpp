#include "animate.h"
#include <iostream>
using namespace std;

animate::animate() : sidebar(WORK_PANEL, SIDE_BAR)
{
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "99_00_final_project-phangtommy");

    _info = new graph_info();

    system.set_info(_info);
    sidebar.set_info(_info);
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    mouseIn = true;
    mousePoint = sf::CircleShape();
    mousePoint.setRadius(2.0);
    mousePoint.setFillColor(sf::Color::Green);

    // cout << "Loading font" << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration

    if (!font.loadFromFile("../arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    
}

// animate::~animate()
// {
//     delete _info;
// }

void animate::Draw()
{
    system.Draw(window);

    if(_info->_tab)
    {
        sidebar.draw(window);
    }
    else
    {
        _coorlabel = sf::Text("(" + to_string(mouseX).substr(0,5) + ", " + to_string(mouseY).substr(0,5) + ")", font);
        _coorlabel.setCharacterSize(24);
        _coorlabel.setStyle(sf::Text::Bold);
        _coorlabel.setFillColor(sf::Color::Yellow);
        _coorlabel.setPosition(sf::Vector2f(mousePoint.getPosition().x , mousePoint.getPosition().y - 40));
        window.draw(_coorlabel);
    }

    if(mouseIn)
    {
        window.draw(mousePoint);
    }

    if(_info->_getInput)
    {
        input_label = sf::Text(_output, font);
        input_label.setCharacterSize(35);
        input_label.setStyle(sf::Text::Bold);
        input_label.setFillColor(sf::Color::Green);
        // input_label.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - input_label.getLocalBounds().height - 5));
        input_label.setPosition(sf::Vector2f(10, 10));
        window.draw(input_label);
    }
}


void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command, _info);
    command = DEFAULT;
    if(mouseIn)
    {
        sf::Vector2f scalar(_info->_window_dimension.x / window.getSize().x ,
                            _info->_window_dimension.y / window.getSize().y);
        
        mousePoint.setPosition(scalar.x * (sf::Mouse::getPosition(window).x - mousePoint.getRadius()),
                               scalar.y * (sf::Mouse::getPosition(window).y - mousePoint.getRadius()));                       
    }

}
void animate::render()
{
    window.clear(sf::Color(33, 33, 33));
    // window.clear(sf::Color::Transparent);
    system.Draw(window);
    Draw();
    window.display();
}

void animate::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode < 128)
                // std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                if(!_info->_getInput && event.text.unicode == 'f')
                {
                    _info->_getInput = true;
                }
                else if(_info->_getInput && event.text.unicode == 'f')
                {
                    _input = "";
                    _output = "f(x) = ";
                    _info->_getInput = false;
                }
                else if(_info->_getInput && event.text.unicode == 8)
                {
                    _input = _input.substr(0, _input.size() - 1);
                    _output = "f(x) = ";
                    _output.append(_input);
                }                                                                                   
                else if(_info->_getInput && event.text.unicode != 'f' && event.text.unicode != 9) // 9 = tab, 13 = enter
                {
                    _input += event.text.unicode;
                    _output += event.text.unicode;
                }
        }

        // [TODO] Screen dragging, maybe fix zoom scaling first?!

        // if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        // {
        //     before.x = event.mouseButton.x;
        //     before.y = event.mouseButton.y;

        //    // cout << "dragging right now" << endl;
        // }
        // if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        // {

        //     after.x = event.mouseButton.x;
        //     after.y = event.mouseButton.y;
        //     // cout << "before: " << before.x << " and " << before.y <<endl;
        //     // cout << "after: " <<  after.x << " and " << after.y << endl;
        //     sf::Vector2f diff (after.x - before.x, after.y - before.y);
        //     // cout << "diff: " <<  diff.x << " and " << diff.y << endl;
        //     // diff.x negative -> right
        //     // diff.y negative -> down

        //     if(diff.y < 0)
        //         command = DOWN;
        //     else
        //         command = UP;

        //     if(diff.x < 0)
        //         command = RIGHT;
        //     else
        //         command = LEFT;
        //     // cout << "already released" << endl;
        // }


        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                // case sf::Keyboard::PageUp:
                    command = UP;
                    break;
                case sf::Keyboard::Down:
                // case sf::Keyboard::PageDown:
                    command = DOWN;
                    break;
                case sf::Keyboard::Left:
                    command = LEFT;
                    break;            
                case sf::Keyboard::Right:
                    command = RIGHT;
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                
                // [MAC dependency -- change key]
                case sf::Keyboard::RBracket:
                    command = ZOOMIN;
                    break;
                case sf::Keyboard::LBracket:
                    command = ZOOMOUT;
                    break;
                case sf::Keyboard::Space:
                    command = RESET;
                    break;
                case sf::Keyboard::Tab:
                    command = TAB;
                    break;
                case sf::Keyboard::Hyphen:
                    command = COOR;
                    break;
                case sf::Keyboard::F1:
                    command = GRID;
                    break;

                // [TODO?] Change user input command to other key
                case sf::Keyboard::Enter:
                    if(_info->_getInput)
                        if(_input != "" && _input != _info->_equation)
                            _info->_equation = _input;
                        if(_input != "")
                            sidebar.setEquation(_info->_equation);

                        _input = "";
                        _output = "f(x) = ";
                        _info->_getInput = false;
                    break;
                case sf::Keyboard::Backslash:
                    sidebar.deleteEquation();
                    break;
            }
            
        case sf::Event::MouseEntered:
            // [TODO] Update displayed coordinate (x,y) whenever panning and not moving mouse
            mouseIn = true;
            break;
        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseButtonPressed:
            switch (event.mouseButton.button)
            {
                // [TODO] Do something for left and right clicks
                case sf::Mouse::XButton1:
                    command = LEFT;
                    break;
                case sf::Mouse::XButton2:
                    command = RIGHT;
                    break;
                case sf::Mouse::Middle:
                    command = RESET;
                    break;
                // case sf::Mouse::Left:
                //     break;
                // case sf::Mouse::Right:
                //     break;
            }

        case sf::Event::MouseWheelScrolled:
            if(event.mouseWheelScroll.delta == 1)       // scroll up
                command = ZOOMIN;
            else if(event.mouseWheelScroll.delta == -1) // scroll down
                command = ZOOMOUT;
            break;

        case sf::Event::MouseMoved:
            // scaled mouse position - scaled distance from origin
            mouseX = ((event.mouseMove.x * _info->_window_dimension.x / window.getSize().x) - (_info->_origin.x + _info->_offset.x)) / _info->_scale.x;
            mouseY = -((event.mouseMove.y *  _info->_window_dimension.y / window.getSize().y) - (_info->_origin.y + _info->_offset.y)) / _info->_scale.y; 

            if(_info->_tab)
            {
                sidebar.mousePos(event.mouseMove.x * _info->_window_dimension.x / window.getSize().x ,
                                 event.mouseMove.y *  _info->_window_dimension.y / window.getSize().y);
            }
            break;

        default:
            break;
        }
    }
}

void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    
    sidebar.closefile();
}

string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}

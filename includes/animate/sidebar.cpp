#include "sidebar.h"
Sidebar::Sidebar()
{
}

void Sidebar::set_info(graph_info* info)
{
    _info = info;
}

Sidebar::Sidebar(float left, float width) : _left(left), _width(width)
{
    rect.setFillColor(sf::Color(40, 40, 40)); //(105,105,105)); 
    // rect.setFillColor(sf::Color::Transparent); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));


    if (!font.loadFromFile("../arial.ttf")) //Roboto-Thin.ttf
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    // OPEN FILE
    fin.open("../../99_00_final_project-phangtommy/history.txt");

	if (fin.fail())
	{
		cout << "history.txt file not found. Current working folder is /build/bin/main" ;
		exit(1);
	}


    // Display history when calling CTOR
    string eq;
    int line = 0;

    while (!fin.eof()) {

        getline(fin, eq);

        if(!eq.empty())
        {
            setEquation(eq);
            line++;
        }
    }
}

void Sidebar::setEquation(string equation)
{
    const double LEFT_MARGIN = 15.0;
    const double VERTICAL_LINE_SPACING = 40.0;

    eq.set_eq(equation);
    eq.set_font(font);
    eq.set_color(sf::Color::Yellow);
    eq.set_pos(sf::Vector2f(_left + LEFT_MARGIN, texthistory.size()* VERTICAL_LINE_SPACING + LEFT_MARGIN));
    texthistory.push_back(eq);

    // texthistory.emplace_back(font, equation, sf::Color::Yellow, sf::Vector2f(_left + LEFT_MARGIN, texthistory.size()* VERTICAL_LINE_SPACING + LEFT_MARGIN));
}

void Sidebar::deleteEquation()
{
    if(texthistory.size())
        texthistory.pop_back();
        if(texthistory.size() >= 1)
            _info->_equation = texthistory.back().getEq();
        else
            _info->_equation = "";
}

void Sidebar::closefile()
{
    fin.close();

    ofstream fout;
    fout.open("../../99_00_final_project-phangtommy/history.txt");

    string word;
    for (int i=0; i<texthistory.size(); i++) 
    {
        word = texthistory[i].getEq();
        fout << word << endl;
    }

    fout.close();
}

void Sidebar::draw(sf::RenderWindow &window)
{
    window.draw(rect);

    for (int i=0; i<texthistory.size(); i++) 
    {
        texthistory[i].draw(window);
    }

    if(_info->_tab)
    {
        // Texthistory del(font, "[del]" , sf::Color::Yellow, sf::Vector2f(SCREEN_WIDTH - del.getGlobalBounds().width - 42, SCREEN_HEIGHT - del.getGlobalBounds().height - 25));
        // del.draw(window);

        _pressDel = sf::Text("[del]", font);
        _pressDel.setCharacterSize(20);
        _pressDel.setFillColor(sf::Color::Yellow);
        _pressDel.setPosition(sf::Vector2f(SCREEN_WIDTH - _pressDel.getLocalBounds().width - 15 , SCREEN_HEIGHT - _pressDel.getLocalBounds().height - 10));
        window.draw(_pressDel);
    }
}

void Sidebar::mousePos(float x, float y)
{
    for (int i=0; i<texthistory.size(); i++) 
    {
        sf::FloatRect textBounds = texthistory[i].getBounds();
        if (textBounds.contains(sf::Vector2f(x,y))) 
        {
            texthistory[i].set_color(sf::Color::Green);
            _info->_equation = texthistory[i].getEq();
        }
        else 
        {
            texthistory[i].set_color(sf::Color::Yellow);
        }
    }
}

#ifndef SYSTEM_H
#define SYSTEM_H
#include "graph_info.h"
#include "graph.h"

class System
{
public:
    System();
    System(graph_info* info);

    void set_info(graph_info* info);
    void Step(int command, graph_info* info);
    void Draw(sf::RenderWindow& window);

private:
    Graph _g;
    graph_info* _info;
    sf::Vector2f offset;
};

#endif // SYSTEM_H

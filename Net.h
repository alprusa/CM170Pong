#ifndef NET_H
#define NET_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class net{
    private:
        int x;
        int y;
        int numNetDashLines;
        int yIncrement;
        sf::VertexArray netShape;
    public:
        net(int dashes, int inc, string orientation);
        sf::VertexArray getNet(){return netShape;}
        sf::Vector2f getXY(){return sf::Vector2f(x, y);}
        ~net(){}
};

#endif

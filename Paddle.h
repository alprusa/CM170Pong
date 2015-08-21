#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class paddle{
    private:
        int width;
        int height;
        int x;
        int textX;
        int y;
        int textY;
        float velocity;
        int score;
        sf::RectangleShape paddleShape;
        sf::Text scoreText;
    public:
        paddle(int xPos, int yPos, string orientation);
        void buildText(sf::RenderWindow& window, int xPos, int yPos);
        void changeScore(int change);
        void changeDirections(string direction, int windowWidth, int windowHeight);

        sf::RectangleShape getPaddleShape();
        sf::Text getText(){return scoreText;}
        int getScore(){return score;}
        int getX(){return x;}
        int getY(){return y;}
        int getWidth(){return width;}
        int getHeight(){return height;}
        int getTextX(){return textX;}
        int getTextY(){return textY;}
        
        ~paddle(){}
};

#endif

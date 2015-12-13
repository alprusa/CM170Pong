#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Paddle.h"

using namespace std;

paddle::paddle(int xPos, int yPos, string orientation):x(xPos), y(yPos){
    width = 15;
    height = 50;
    velocity = 1;
    score = 0;

    //build the paddle
    if(orientation == "vertical") paddleShape = sf::RectangleShape(sf::Vector2f(width, height));
    else paddleShape = sf::RectangleShape(sf::Vector2f(height, width));
    paddleShape.setFillColor(sf::Color::White);
    paddleShape.setPosition(x, y);
}

//build the score text
void paddle::buildText(sf::RenderWindow& window, int xPos, int yPos){
    sf::Font stdFont;
    if(!stdFont.loadFromFile("OpenSans-Regular.ttf")) return;
    scoreText.setFont(stdFont);
    stringstream scoreSStream;
    scoreSStream << score;
    string scoreS;
    scoreSStream >> scoreS;
    scoreText.setString(scoreS);
    scoreText.setCharacterSize(30);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(xPos, yPos);
    window.draw(scoreText);
}

void paddle::changeScore(int change){
    change <= 0 ? score = 0 : score += change;
}

sf::RectangleShape paddle::getPaddleShape(){
    return paddleShape;
}

//Change the direction of the y mouse
//case 0 is for player one using WASD
//case 1 of switch statement si for player using arrow keys
void paddle::changeDirections(int playerNum, int windowWidth, int windowHeight, bool horizontalPaddle){
    int minY = 5;
    int maxY = (windowHeight - 55);
    int minX = 40;
    int maxX = (windowWidth - 95);

    switch(playerNum){
        case 0:
            //move up if the player has not reached the top of the screen and they are pressing W
            if(!horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y > minY)
                y -= velocity;

            //move down if player has not reached the bottom of the window and they are pressing S
            if(!horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y < maxY)
                y += velocity;

            //move left if player has not reached the left of the window and they are pressing A
            if(horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x > minX)
                x -= velocity;

            //move right if player has not reached the right of the window and they are pressing D
            if(horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x < maxX)
                x += velocity;
            break;
        case 1:
            //move up if the player has not reached the top of the screen and they are pressing up arrow
            if(!horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && y > minY)
                y -= velocity;

            //move down if player has not reached the bottom of the window and they are pressing down arrow
            if(!horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && y < maxY)
                y += velocity;

            //move left if player has not reached the left of the window and they are pressing left arrow
            if(horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x > minX)
                x -= velocity;

             //move right if player has not reached the right of the window and they are pressing right arrow
            if(horizontalPaddle && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x < maxX)
                x += velocity;
            break;
    }

    paddleShape.setPosition(x, y);
}

void paddle::changePaddlePosition(int xPos, int yPos){
    x = xPos;
    y = yPos;
    paddleShape.setPosition(xPos, yPos);
}

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
    paddleShape.setPosition(x, y);
    return paddleShape;
}


//Change the direction of the y mouse
void paddle::changeDirections(string direction, int windowWidth, int windowHeight){
    if(direction == "up" && y > 5)
        y -= velocity;
    else if(direction == "down" && y < (windowHeight - 55))
        y += velocity;

    if(direction == "left" && x > 40)
        x -= velocity;
    else if(direction == "right" && x < (windowWidth - 95))
        x += velocity;
}

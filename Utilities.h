#ifndef UTILITIES_H
#define UTILITIES_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Ball.h"
#include "Paddle.h"

using namespace std;

void menuOptionScreen(sf::RenderWindow& window, sf::Font stdFont, int x, int y, string text);

void restart(paddle& p1, paddle& p2, paddle& p3, paddle& p4, ball& b);

string optionsScreen(int* toggleOptions, int& action);

#endif

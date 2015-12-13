#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"
#include "AI.h"

void paddleAI::movePaddle(ball b, paddle& pR, paddle& pB, int windowWidth, int windowHeight){
	float ballXLoc = b.getX();
	float ballYLoc = b.getY();

	int minY = 5;
    int maxY = (windowHeight - 55);
    int minX = 40;
    int maxX = (windowWidth - 95);
    int ballThreshold = 250;

    int x = pB.getX();
    int y = pR.getY();

    //when the player on the upper half of the screen move ai paddle up till it hits the top
	if(ballYLoc < ballThreshold && y > minY)
		y = pR.getY() - pR.getVelocity();

    //when the player is half-way down the screen move ai paddle down till it hits the bottom
	if(ballYLoc > ballThreshold && y < maxY)
		y = pR.getY() + pR.getVelocity();

    //when the player on the left half of the screen move ai paddle left till it hits the left side of screen
	if(multipaddle && ballXLoc < ballThreshold && x > minX)
		x = pB.getX() - pB.getVelocity();

    //when the player on the right half of the screen move ai paddle right till it hits the right side of screen
	if(multipaddle && ballXLoc > ballThreshold && x < maxX)
		x = pB.getX() + pB.getVelocity();

    pR.changePaddlePosition(pR.getX(), y);
    if(multipaddle) pB.changePaddlePosition(x, pB.getY());
}

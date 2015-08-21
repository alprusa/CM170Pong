#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"
#include "AI.h"

void paddleAI::movePaddle(ball b, paddle& pR, paddle& pB, int windowWidth, int windowHeight){
	float ballXLoc = b.getX();
	float ballYLoc = b.getY();

	if(ballYLoc > 250)
		pR.changeDirections("down", windowWidth, windowHeight);
	else
		pR.changeDirections("up", windowWidth, windowHeight);

	if(ballXLoc > 250)
		pB.changeDirections("right", windowWidth, windowHeight);
	else
		pB.changeDirections("left", windowWidth, windowHeight);
}

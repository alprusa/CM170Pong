#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Ball.h"
#include "Paddle.h"

using namespace std;

ball::ball(float sz, float xPos, float yPos):size(sz), x(xPos), y(yPos){
	gravity = 1.0;
	mass = 0.8;
	velocityX = 0;
	velocityY = 0;

	srand(time(0));
	if(rand() % 2 == 0) {
		accelerationX = 0.3;
		accelerationY = mass*gravity*0.3;
	}
	else {
		accelerationX = -0.3;
		accelerationY = -mass*gravity*0.3;
	}

    ballShape = sf::CircleShape(size);
    ballShape.setFillColor(sf::Color::White);
    ballShape.setPosition(x,y);
}

sf::CircleShape ball::getBall(){
	ballShape.setPosition(x,y);
	return ballShape;
}

bool ball::collisionCheck(paddle& p){
	return x < (p.getX() + p.getWidth()) && (x + size) > p.getX() &&
		y < (p.getY() + p.getHeight()) && (y + size) > p.getY();
}

/*bool collisionCheckTopBottom(paddle& p){
	return x < (p.getX() + p.getWidth()) && (x + size) > p.getX() &&
		y < ((p.getY() + p.getHeight()/2) + p.getHeight()/2) && (y + size) > (p.getY() + p.getHeight()/2);
}*/

void ball::bounceOff(int playerBounced){
	if(playerBounced == 0) {
		//accelerationY += accelerationX;
		accelerationX = -accelerationX;
		velocityX = -velocityX;
	}
	if(playerBounced == 1) {
		accelerationY += accelerationX;
		accelerationX = -accelerationX;
		velocityX = -velocityX;
	}
	if(playerBounced == 2){
		accelerationX += accelerationY;
		accelerationY = -accelerationY;
	}

	x += (velocityX + accelerationX);
	y += (velocityY + accelerationY);
}

int ball::move(int windowWidth, int windowHeight){
	float height = float(windowHeight) - y; //height of ball to bottom

	//stop the ball from going to fast
	//velocityY > sqrt(2*gravity*height) ? velocityY = sqrt(2*gravity*height) - accelerationY : false;
	accelerationY > sqrt(2*gravity*height) ? accelerationY = sqrt(2*gravity*height) : false;

	//velocityX > 0.6 ? velocityX = 0.6 - accelerationX : false;
	accelerationX > 0.6 ? accelerationX = 0 : false;

	//make sure that ball doesn't stop moving
	accelerationX < 0.2 && accelerationX > -0.2 ? accelerationX = 0.4 : false;

	accelerationY < 0.2 && accelerationY > -0.2 ? accelerationY = 0.4 : false;

	//increase the speed of ball
	x += (velocityX + accelerationX);
	y += (velocityY + accelerationY);

	//player score indicators 0 = none, 1 = first, 2 = second

	if(x > (windowWidth + 30)) {
		velocityX = 0;
		velocityY = 0;
		accelerationX = -0.3;
		accelerationY = mass*gravity*0.3;
		x = 250;
		y = 250;
		return 1;
	}
	if(x < -30){
		velocityX = 0;
		velocityY = 0;
		accelerationX = 0.3;
		accelerationY = -mass*gravity*0.3;
		x = 250;
		y = 250;
		return 2;
	}

	//for conditions involving multipaddle mode
	if((y > (windowHeight - 20) || y < 4) && !multipaddle) {
		accelerationX += accelerationY;
		accelerationY = -accelerationY;
	}
	else if(multipaddle){
		if(y > (windowHeight - 20)) {
			velocityX = 0;
			velocityY = 0;
			accelerationX = -0.3;
			accelerationY = mass*gravity*0.3;
			x = 250;
			y = 250;
			return 1;
		}
		if(y < 4){
			velocityX = 0;
			velocityY = 0;
			accelerationX = 0.3;
			accelerationY = -mass*gravity*0.3;
			x = 250;
			y = 250;
			return 2;
		}
	}

	return 0;
}

void ball::changeAcceleration(float xIncAmount, float yIncAmount){
	accelerationX += xIncAmount;
	accelerationY += yIncAmount;
}

void ball::changeMassSize(float m, float sz){
	mass = m;
	size = sz;
	ballShape = sf::CircleShape(size);
}

void ball::changeX(float xPos, string math){
	if(math == "add")
		x += xPos;
	if(math == "sub")
		x -=xPos;
}

void ball::changeY(float yPos, string math){
	if(math == "add")
		y += yPos;
	if(math == "sub")
		y -= yPos;
}

void ball::absorb(paddle& p1, paddle& p2){
	//make ball get pulled to center
	velocityX = 0;
	velocityY = 0;
	srand(time(0));
	if(rand() % 2 == 0) {
		accelerationX = 0.2;
		accelerationY = mass*gravity*0.2;
	}
	else {
		accelerationX = -0.2;
		accelerationY = -mass*gravity*0.2;
	}
	x = 250;
	y = 250;

	//if taken then players will lose a point unless at 0
	p1.changeScore(-1);
	p2.changeScore(-1);
}

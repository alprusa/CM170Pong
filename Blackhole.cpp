#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Blackhole.h"
#include "Ball.h"

using namespace std;

blackhole::blackhole(int sz, int pts):size(sz), numPoints(pts){
	x = 220;
	y = 200;
	hole = sf::CircleShape(size,numPoints);
	hole.setFillColor(sf::Color::Blue);
    hole.setPosition(x,y);
}

sf::CircleShape blackhole::getShape(){
	hole.setPosition(x,y);
	return hole;
}

bool blackhole::collisionCheck(ball& b){
	return x < (b.getX() + b.getSize()) && (x + size) > b.getX() &&
		y < (b.getY() + b.getSize()) && (y + size) > b.getY();
}

void blackhole::pullBall(ball& b, float pull){
	if(x > 500 || y > 500) return;

	//bottom right
	if(b.getX() > 250 && b.getY() > 250){
		b.changeX(pull, "add");
		b.changeY(pull, "sub");
	}
	//bottom left
	if(b.getX() > 250 && b.getY() < 250){
		//b.changeX(pull, "add");
		b.changeY(pull, "add");
	}
	//top left
	if(b.getX() < 250 && b.getY() < 250){
		b.changeX(pull, "add");
		b.changeY(pull, "add");
	}
	//top right
	if(b.getX() < 250 && b.getY() > 250){
		//b.changeX(pull, "sub");
		b.changeY(pull, "add");
	}
}

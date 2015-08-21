#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"

using namespace std;

class blackhole{
	private:
		int size;
		int numPoints;
		float x;
		float y;

		sf::CircleShape hole;
	public:
		blackhole(int sz, int pts);
		sf::CircleShape getShape();
		void pullBall(ball& b, float pull);

		int getSize(){return size;}
		float getX(){return x;}
		float getY(){return y;}
		bool collisionCheck(ball& b);

		~blackhole(){}
};

#endif

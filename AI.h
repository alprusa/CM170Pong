#ifndef AI_H
#define AI_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

using namespace std;

class paddleAI{
	private:
		bool multipaddle;

	public:
		paddleAI(bool mP):multipaddle(mP){}
		void movePaddle(ball b, paddle& pR, paddle& pB, int windowWidth, int windowHeight);
		void isMultiPaddle(bool mP){multipaddle = mP;}
		~paddleAI(){}
};

#endif

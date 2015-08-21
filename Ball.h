#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paddle.h"

using namespace std;

class ball{
    private:
        float size;
        float x;
        float y;
        float mass;

        float velocityX;
        float accelerationX;
        float velocityY;
        float accelerationY;
        float gravity;

        sf::CircleShape ballShape;
    public:
        ball(float sz, float xPos, float yPos);
        
        int move(int windowWidth, int windowHeight);
        bool collisionCheck(paddle& p);
        void bounceOff(int playerBounced);
        void absorb(paddle& p1, paddle& p2);

        void changeMassSize(float m, float sz);
        void changeAcceleration(float xIncAmount, float yIncAmount);
        void changeX(float xPos, string math);
        void changeY(float yPos, string math);

        bool multipaddle;
        bool challenge;
        bool spawn;

        sf::CircleShape getBall();
        float getSize(){return size;}
        float getX(){return x;}
        float getY(){return y;}
        ~ball(){}
};

#endif

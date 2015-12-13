/*things to fix in the furture
//make blackhole do pulling better
//make simple ai more complex
//fix the pong ball physics
//add that ball will speed up when players have been going back and forth for a while*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "Paddle.h"
#include "Net.h"
#include "Ball.h"
#include "Blackhole.h"
#include "AI.h"
#include "Utilities.h"
#include "Sounds.h"

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(500, 500), "Pong");

    //create audio
    Sounds paddleSound("Paddle");//"beep-04.wav"
    Sounds endSound("Finish"); //"tennis-ball-hit-02.wav"
    Sounds goalSound("Goal");//"bicycle-bell-ring-01.wav"

    //The Ball
    ball ball1(10, 250, 250);

    //Font for Scores
    sf::Font stdFont;
    if(!stdFont.loadFromFile("OpenSans-Regular.ttf")) return 1;

    //The Paddles
    paddle paddle1(10, 20, "vertical"); //paddle left
    paddle paddle2(470, 20, "vertical"); //paddle right
    paddle paddle3(40, 20, "horizontal"); //paddle top
    paddle paddle4(405, 460, "horizontal"); //paddle bottom

    //Ai System
    paddleAI ai(false);

    //The Net
    net net1(26, 20,"vertical");
    net net2(26, 20, "horizontal");

    //the blackhole challenge mode
    blackhole bh1(30,8);

    int action = 0; //start = 0, options = 1, pause = 2, 3 = one player, 4 = two player
    //audio = 0, endless = 1, challenge = 2, multi-paddle = 3
    int toggleOptions[4] = {true, false, false, false};
    string playerWin = "a Tie";

    //For creating and closing the game window
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        switch(action){
            case 0:
            {
                window.clear();

                //Text For Starting the Game
                string startOptions = "Pong Remake\n1 Player (1)\n2 Player (2)\nOptions (3)";
                menuOptionScreen(window, stdFont, 150, 150, startOptions);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) action = 3;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) action = 4;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) action = 1;

                restart(paddle1, paddle2, paddle3, paddle4, ball1);
                bh1.pullBall(ball1, 0);
                ball1.spawn = true;
                break;
            }
            case 1:
            {
                window.clear();

                //the options menu
                string optsT = optionsScreen(toggleOptions, action);

                menuOptionScreen(window, stdFont, 30, 150, optsT);
                break;
            }
            case 2:
            {
                if(toggleOptions[0]) endSound.getSound().play();

                //Text to let the players know game ended
                string winTextString = "The Winnner is " + playerWin + "\nPress R to Restart";

                sf::Text optionText;
                optionText.setFont(stdFont);
                optionText.setString(winTextString);
                optionText.setCharacterSize(30);
                optionText.setStyle(sf::Text::Bold);
                optionText.setColor(sf::Color::Red);
                optionText.setPosition(100, 200);
                window.draw(optionText);

                restart(paddle1, paddle2, paddle3, paddle4, ball1);
                bh1.pullBall(ball1, 0);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) action = 0;
                break;
            }
            default:
            {
                //size of the window converted to int from unsigned int
                int windowHeight = int(window.getSize().y);
                int windowWidth = int(window.getSize().x);

                window.clear();

                //Paddle1/PLayer1 Draw
                paddle1.changeDirections(0, windowWidth, windowHeight, false);
                window.draw(paddle1.getPaddleShape()); //draw 1st paddle (right)
                if(toggleOptions[3]) {
                    paddle3.changeDirections(0, windowWidth, windowHeight, true);
                    window.draw(paddle3.getPaddleShape()); //draw 3rd paddle (top) if multipaddle is on
                }
                paddle1.buildText(window,200,10); //score text

                //Paddle2/PLayer2 Draw
                //check is player is against AI
                if(action != 3){
                    paddle2.changeDirections(1, windowWidth, windowHeight, false);
                    if(toggleOptions[3]) paddle4.changeDirections(1, windowWidth, windowHeight, true);
                }
                else{
                    ai.movePaddle(ball1, paddle2, paddle4, windowWidth, windowHeight);
                }
                window.draw(paddle2.getPaddleShape()); //draw the 2nd paddle (left)
                if(toggleOptions[3]) window.draw(paddle4.getPaddleShape()); //draw the 4th paddle (bottom) if multipaddle mode is active
                paddle2.buildText(window,280,10); //score text

                //mulit-paddle mode
                if(toggleOptions[3]){
                    if(action == 3) ai.isMultiPaddle(true); //make multipaddle mode active for AI

                    //horizontal net
                    window.draw(net2.getNet());
                }
                else ai.isMultiPaddle(false);

                //net vertical
                window.draw(net1.getNet());

                //blackhole for challenge mode
                if(toggleOptions[2]){
                    window.draw(bh1.getShape());
                }

                //Ball
                if(toggleOptions[2]){
                    ball1.changeMassSize(0.5, 5);
                    //just add black hole here
                }
                int playerScored = ball1.move(windowWidth, windowHeight);

                //collison detection for ball
                bool p1Bounce = ball1.collisionCheck(paddle1);
                if(p1Bounce) {
                    if(toggleOptions[0]) paddleSound.getSound().play();
                    ball1.bounceOff(0);
                    ball1.spawn = false;
                }

                bool p2Bounce = ball1.collisionCheck(paddle2);
                if(p2Bounce) {
                    if(toggleOptions[0]) paddleSound.getSound().play();
                    ball1.bounceOff(1);
                    ball1.spawn = false;
                }

                //for mulit-paddle mode
                if(toggleOptions[3]){
                    ball1.multipaddle = true;
                    bool p3Bounce = ball1.collisionCheck(paddle3);
                    if(p3Bounce) {
                        if(toggleOptions[0]) paddleSound.getSound().play();
                        ball1.bounceOff(2);
                    }

                    bool p4Bounce = ball1.collisionCheck(paddle4);
                    if(p4Bounce) {
                        if(toggleOptions[0]) paddleSound.getSound().play();
                        ball1.bounceOff(2);
                    }
                }
                else ball1.multipaddle = false;

                //for challenge mode
                if(toggleOptions[2] && !ball1.spawn){
                    ball1.challenge = true;
                    bool blackHoleOb = bh1.collisionCheck(ball1);
                    if(blackHoleOb) {
                        //if(toggleOptions[0]) playAbsorbSound();
                        ball1.absorb(paddle1, paddle2);
                        ball1.spawn = true;
                    }
                    if(!p1Bounce && !p2Bounce)
                        bh1.pullBall(ball1, 0.2);
                }
                else ball1.challenge = false;

                window.draw(ball1.getBall());

                //check to change Scores
                if(playerScored == 1) {
                    if(toggleOptions[0]) goalSound.getSound().play();
                    paddle1.changeScore(1);
                    ball1.spawn = true;
                }
                else if(playerScored == 2) {
                    if(toggleOptions[0]) goalSound.getSound().play();
                    paddle2.changeScore(1);
                    ball1.spawn = true;
                }

                //exit the game
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) action = 0;

                //determine if there was a winner
                if((paddle1.getScore() >= 3 || paddle2.getScore() >= 3) && !toggleOptions[1]) {
                    if(paddle1.getScore() != paddle2.getScore())
                        paddle1.getScore() > paddle2.getScore() ? playerWin = "Player 1" : playerWin = "Player 2";
                    action = 2;
                }

                break;
            }
        }

        window.display();
    }

    return 0;
}

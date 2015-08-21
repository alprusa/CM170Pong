/*things to fix in the furture
//make blackhole do pulling better
//see if audio can be fixed as in be put in class or function
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
//#include "Sounds.h"

using namespace std;

//to get what the height of the window is
template<typename WINDOWY>
int heightConvert(WINDOWY wy){
    return int(wy);
}

//to get what the width of the window is
template<typename WINDOWX>
int widthConvert(WINDOWX wX){
    return int(wX);
}

//the options can turn off/on music and turn off/on score limit so you can endless play
//turn on/off the black hole component turn on/off multi-paddle mode or classic mode
void menuOptionScreen(sf::RenderWindow& window, sf::Font stdFont, int x, int y, string text){
    sf::Text optionText;
    optionText.setFont(stdFont);
    optionText.setString(text);
    optionText.setCharacterSize(30);
    optionText.setStyle(sf::Text::Bold);
    optionText.setColor(sf::Color::White);
    optionText.setPosition(x, y);
    window.draw(optionText);
}

void restart(paddle& p1, paddle& p2, paddle& p3, paddle& p4, ball& b){
    ball ball1(10, 250, 250);
    paddle paddle1(10, 20, "vertical");
    paddle paddle2(470, 20, "vertical");
    paddle paddle3(40, 20, "horizontal"); //paddle top
    paddle paddle4(405, 460, "horizontal"); //paddle bottom

    p1 = paddle1;
    p2 = paddle2;
    p3 = paddle3;
    p4 = paddle4;
    b = ball1;
}

int main(){
    sf::RenderWindow window(sf::VideoMode(500, 500), "Pong");

    //create audio
    //Sounds paddleSound("Paddle");//"beep-04.wav"
    //Sounds endSound("Finish"); //"tennis-ball-hit-02.wav"
    //Sounds goalSound("Goal");//"bicycle-bell-ring-01.wav"
    sf::SoundBuffer buf;
    //const string& sndName = fileName;
    if(!buf.loadFromFile("beep-04.wav")) return -1;
    sf::Sound sndAudio;
    sndAudio.setBuffer(buf);

    sf::SoundBuffer buf2;
    //const string& sndName = fileName;
    if(!buf2.loadFromFile("bicycle-bell-ring-01.wav")) return -1;
    sf::Sound sndAudioG;
    sndAudioG.setBuffer(buf2);

    sf::SoundBuffer buf3;
    //const string& sndName = fileName;
    if(!buf3.loadFromFile("tennis-ball-hit-02.wav")) return -1;
    sf::Sound sndAudioE;
    sndAudioE.setBuffer(buf3);

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
                string optsT;
                string onOff;
                //the audio
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) toggleOptions[0] = !toggleOptions[0];
                toggleOptions[0] ? onOff = "on" :  onOff = "off";
                optsT = "Audio " + onOff + "(1)";

                //endless mode
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) toggleOptions[1] = !toggleOptions[1];
                toggleOptions[1] ? onOff = "on" :  onOff = "off";
                optsT += ("\nEndless Mode " + onOff + "(2)");

                //challenge mode ball is smaller faster and there is a black hole trying to absorb it
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) toggleOptions[2] = !toggleOptions[2];
                toggleOptions[2] ? onOff = "on" :  onOff = "off";
                optsT += ("\nChallenge Mode " + onOff + "(3)");

                //multi-paddle mode player has two paddles top/bottom and left/right can score from any side
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) toggleOptions[3] = !toggleOptions[3];
                toggleOptions[3] ? onOff = "on" :  onOff = "off";
                optsT += ("\nMulti-Paddle Mode " + onOff + "(4)");

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) action = 0;
                optsT += "\nBack (Escape)";

                menuOptionScreen(window, stdFont, 30, 150, optsT);
                break;
            }
            case 2:
            {
                if(toggleOptions[0]) sndAudioE.play();//endSound.playSound();

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
                //size of the window
                int windowHeight = heightConvert(window.getSize().y);
                int windowWidth = widthConvert(window.getSize().x);

                window.clear();

                //Paddle1/PLayer1 Draw
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    paddle1.changeDirections("up", windowWidth, windowHeight);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    paddle1.changeDirections("down", windowWidth, windowHeight);
                window.draw(paddle1.getPaddleShape());
                paddle1.buildText(window,200,10); //score text

                //Paddle2/PLayer2 Draw
                if(action != 3){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        paddle2.changeDirections("up", windowWidth, windowHeight);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        paddle2.changeDirections("down", windowWidth, windowHeight);
                }
                else{
                    ai.movePaddle(ball1, paddle2, paddle4, windowWidth, windowHeight);
                }
                window.draw(paddle2.getPaddleShape());
                paddle2.buildText(window,280,10); //score text

                //mulit-paddle mode
                if(toggleOptions[3]){
                    ai.isMultiPaddle(true);

                    //Paddle3/Player1
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        paddle3.changeDirections("left", windowWidth, windowHeight);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        paddle3.changeDirections("right", windowWidth, windowHeight);
                    window.draw(paddle3.getPaddleShape());

                    //Paddle4/Player2
                    if(action != 3){
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                            paddle4.changeDirections("left", windowWidth, windowHeight);
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                            paddle4.changeDirections("right", windowWidth, windowHeight);
                    }
                    window.draw(paddle4.getPaddleShape());

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
                    if(toggleOptions[0]) sndAudio.play();//paddleSound.playSound();
                    ball1.bounceOff(0);
                    ball1.spawn = false;
                }

                bool p2Bounce = ball1.collisionCheck(paddle2);
                if(p2Bounce) {
                    if(toggleOptions[0]) sndAudio.play();//paddleSound.playSound();
                    ball1.bounceOff(1);
                    ball1.spawn = false;
                }

                //for mulit-paddle mode
                if(toggleOptions[3]){
                    ball1.multipaddle = true;
                    bool p3Bounce = ball1.collisionCheck(paddle3);
                    if(p3Bounce) {
                        if(toggleOptions[0]) sndAudio.play();//paddleSound.playSound();
                        ball1.bounceOff(2);
                    }

                    bool p4Bounce = ball1.collisionCheck(paddle4);
                    if(p4Bounce) {
                        if(toggleOptions[0]) sndAudio.play();//paddleSound.playSound();
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
                    if(toggleOptions[0]) sndAudioG.play();//goalSound.playSound();
                    paddle1.changeScore(1);
                    ball1.spawn = true;
                }
                else if(playerScored == 2) {
                    if(toggleOptions[0]) sndAudioG.play();//goalSound.playSound();
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

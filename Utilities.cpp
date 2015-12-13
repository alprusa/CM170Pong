#include "Utilities.h"

string optionsScreen(int* toggleOptions, int& action){
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

    return optsT;
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

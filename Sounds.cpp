#include "Sounds.h"
#include <SFML/Audio.hpp>
#include <iostream>

Sounds::Sounds(string snd){
    if(snd == "Paddle") fileName = "beep-04.wav";
    if(snd == "Goal") fileName ="bicycle-bell-ring-01.wav";
    if(snd == "Finish") fileName = "tennis-ball-hit-02.wav";
}

sf::Music& Sounds::getSound(){
    if(!sndAudio.openFromFile(fileName)) throw -1;
    return sndAudio;
}

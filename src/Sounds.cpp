#include "Sounds.h"
#include <SFML/Audio.hpp>
#include <iostream>



Sounds::Sounds(string snd):fileName(snd){
    if(fileName == "Paddle") fileName = "beep-04.wav";
    if(fileName == "Goal") fileName ="bicycle-bell-ring-01.wav";
    if(fileName == "Finish") fileName = "tennis-ball-hit-02.wav";
    sf::SoundBuffer buf;
    const string& sndName = fileName;
    if(!buf.loadFromFile("beep-04.wav")) return;
    sf::Sound sndAudio;
    sndAudio.setBuffer(buf);
    sndAudio.play();
}

void Sounds::playSound(){

    cout << "should play" << endl;
}

#ifndef SOUNDS_H
#define SOUNDS_H

#include <SFML/Audio.hpp>

using namespace std;

class Sounds
{
    private:
        string fileName;
        sf::Music sndAudio;
    public:
        Sounds(string snd);
        sf::Music& getSound();
        ~Sounds(){}
};

#endif // SOUNDS_H

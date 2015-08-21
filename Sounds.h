#ifndef SOUNDS_H
#define SOUNDS_H

#include <SFML/Audio.hpp>

using namespace std;

class Sounds
{
    private:
        string fileName;
    public:
        Sounds(string snd);
        void playSound();
        ~Sounds(){}
};

#endif // SOUNDS_H

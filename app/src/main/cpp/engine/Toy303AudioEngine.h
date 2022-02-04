//
// Created by Mikhail Olshanskii on 03.10.2021.
//

#ifndef TOY3OH3_TOY303AUDIOENGINE_H
#define TOY3OH3_TOY303AUDIOENGINE_H

#include <oboe/Oboe.h>
#include "Voice.h"

class Toy303AudioEngine {
public:
    Toy303AudioEngine();

    oboe::Result startEngine();

    oboe::Result stopEngine();

    void playNote(int note, int octave);

    void releaseNote();

    void setVolume(double volume);

private:

    oboe::Result openPlaybackStream();

    std::shared_ptr<oboe::AudioStream> mStream;

    std::unique_ptr<Voice> toy303Callback;

};

#endif //TOY3OH3_TOY303AUDIOENGINE_H

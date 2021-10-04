//
// Created by Mikhail Olshanskii on 03.10.2021.
//

#ifndef TOY3OH3_TOY303AUDIOENGINE_H
#define TOY3OH3_TOY303AUDIOENGINE_H

#include <oboe/Oboe.h>
#include "Toy303Callback.h"

class Toy303AudioEngine {
public:
    Toy303AudioEngine();

    oboe::Result startEngine();

    oboe::Result stopEngine();

    void beep(bool isBeepOn);

private:

    oboe::Result openPlaybackStream();

    std::shared_ptr<oboe::AudioStream> mStream;

    Toy303Callback *toy303Callback;

};

#endif //TOY3OH3_TOY303AUDIOENGINE_H

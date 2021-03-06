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

    void setPhaseLength(int lengthMillis, Phase phase);

    void setSustainLevel(double  sustain);

    void setWaveform(WaveForm waveForm);

    void setCutoffFrequency(int frequencyHz);

    void setFilterQ(double q);

private:

    const char *TAG = "Toy303AudioEngine";

    oboe::Result openPlaybackStream();

    std::shared_ptr<oboe::AudioStream> mStream;

    std::unique_ptr<Voice> toy303Callback;

};

#endif //TOY3OH3_TOY303AUDIOENGINE_H

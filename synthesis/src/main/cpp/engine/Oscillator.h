//
// Created by Mikhail Olshanskii on 15.10.2021.
//

#ifndef TOY3OH3_OSCILLATOR_H
#define TOY3OH3_OSCILLATOR_H

#include <oboe/Oboe.h>
#include <atomic>
#include "android/log.h"

constexpr double kDefaultFrequency = 440.0;

static constexpr double kPi = M_PI;
static constexpr double kTwoPi = kPi * 2;

enum WaveForm {
    SINE, SAWTOOTH, PULSE
};

class Oscillator {

public:

    Oscillator();

    float nexSample();

    inline void setWaveOn(bool waveOn) {
        isWaveOn = waveOn;
    }

    void setFrequency(double freq);

    void setWaveForm(WaveForm newWaveForm);

    WaveForm getWaveForm();

private:
    float mPhase = 0.0;
    WaveForm mWaveForm = SAWTOOTH;

    bool isWaveOn = true;

    static constexpr int kDefaultSampleRate = 48000;

    std::atomic<double> mPhaseIncrement{
            (kTwoPi * kDefaultFrequency) / static_cast<double>(kDefaultSampleRate)};

    float nextSample(WaveForm waveForm) const;
};


#endif //TOY3OH3_OSCILLATOR_H

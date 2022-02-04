//
// Created by Mikhail Olshanskii on 15.10.2021.
//

#ifndef TOY3OH3_OSCILLATOR_H
#define TOY3OH3_OSCILLATOR_H

#include <oboe/Oboe.h>
#include <atomic>
#include "android/log.h"
#include "Envelope.h"

constexpr double kDefaultFrequency = 440.0;

static constexpr double kPi = M_PI;
static constexpr double kTwoPi = kPi * 2;

enum WaveForm {
    SINE, SAWTOOTH, PULSE
};

class Oscillator {

public:

    Oscillator();

    void render(float *audioData, int32_t numFrames);

    void setWaveOn(bool isWaveOn);

    void setFrequency(double freq);

    void setWaveForm(WaveForm newWaveForm);

    WaveForm getWaveForm();

private:
    float mPhase = 0.0;
    WaveForm mWaveForm = SAWTOOTH;

    std::atomic<double> mPhaseIncrement{
            (kTwoPi * kDefaultFrequency) / static_cast<double>(kDefaultSampleRate)};

    std::unique_ptr<Envelope> envelope;

    float nextSample(WaveForm waveForm);
};


#endif //TOY3OH3_OSCILLATOR_H

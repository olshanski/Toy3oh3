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

class Oscillator {
    //~Oscillator() = default;

public:

    Oscillator();

    void render(float *audioData, int32_t numFrames);

    void setWaveOn(bool isWaveOn) {
        if (isWaveOn) {
            envelope->keyPressed();
        } else {
            envelope->keyReleased();
        }

        isWaveOn_.store(true);
    }

    void setFrequency(double freq) {
        mPhaseIncrement.store((kTwoPi * freq) / static_cast<double>(kDefaultSampleRate));
    }

private:
    float mPhase = 0.0;

    std::atomic<float> mAmplitude{0.2};
    std::atomic<double> mPhaseIncrement{
            (kTwoPi * kDefaultFrequency) / static_cast<double>(kDefaultSampleRate)};
    std::atomic<bool> isWaveOn_{false};

    std::unique_ptr<Envelope> envelope;
};


#endif //TOY3OH3_OSCILLATOR_H

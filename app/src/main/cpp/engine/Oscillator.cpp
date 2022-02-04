//
// Created by Mikhail Olshanskii on 15.10.2021.
//

#include "Oscillator.h"
#include "android/log.h"

Oscillator::Oscillator() {
    __android_log_print(ANDROID_LOG_DEBUG, "Oscillator", "Initialized oscillator");
}

float Oscillator::nexSample() {
    if (!isWaveOn) {
        return false;
    }

    float value = 0.0;

    value = nextSample(mWaveForm);

    mPhase += mPhaseIncrement;
    if (mPhase > kTwoPi) mPhase -= kTwoPi;

    return value;
}

void Oscillator::setFrequency(double freq) {
    mPhaseIncrement.store((kTwoPi * freq) / static_cast<double>(kDefaultSampleRate));
}

void Oscillator::setWaveForm(WaveForm newWaveForm) {
    mWaveForm = newWaveForm;
}

WaveForm Oscillator::getWaveForm() {
    return mWaveForm;
}

float Oscillator::nextSample(WaveForm waveForm) const {
    switch (waveForm) {
        case SINE:
            return sinf(mPhase);
        case SAWTOOTH:
            return (float) (1.0 - (2.0 * mPhase / (kTwoPi)));
        case PULSE:
            if (mPhase < kPi) {
                return 1.0;
            } else {
                return -1.0;
            }
    }
}

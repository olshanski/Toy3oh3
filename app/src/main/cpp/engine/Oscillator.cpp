//
// Created by Mikhail Olshanskii on 15.10.2021.
//

#include "Oscillator.h"
#include "android/log.h"

Oscillator::Oscillator() {
    envelope = std::make_unique<Envelope>();

    __android_log_print(ANDROID_LOG_DEBUG, "Oscillator", "Initialized oscillator");
}

void Oscillator::render(float *audioData, int32_t numFrames) {

    if (envelope->getPhase() == IDLE) {
        mPhase = 0.0;
        for (int i = 0; i < numFrames; i++) {
            audioData[i] = 0.0;
        }
        return;
    }

    for (int i = 0; i < numFrames; ++i) {
        if (envelope->getPhase() == IDLE) {
            envelope->renderFrame();
            audioData[i] = 0.0;
            return;
        } else {
            audioData[i] = nextSample(mWaveForm);
            mPhase += mPhaseIncrement;
            if (mPhase > kTwoPi) mPhase -= kTwoPi;
        }

        audioData[i] *= envelope->renderFrame();
    }
}

void Oscillator::setWaveOn(bool isWaveOn) {
    if (isWaveOn) {
        envelope->enterPhase(ATTACK);
    } else {
        envelope->enterPhase(RELEASE);
    }
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

float Oscillator::nextSample(WaveForm waveForm) {
    switch (waveForm) {
        case SINE:
            return sinf(mPhase);
        case SAWTOOTH:
            return (float) (1.0 - (2.0 * mPhase / (kPi * 2)));
        case PULSE:
            if (mPhase < kPi) {
                return 1.0;
            } else {
                return -1.0;
            }
    }
}

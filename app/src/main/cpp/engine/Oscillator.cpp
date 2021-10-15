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

    if (!isWaveOn_.load()) {
        return;
        mPhase = 0.0;
    }

    for (int i = 0; i < numFrames; ++i) {
        //audioData[i] = sinf(mPhase) * mAmplitude;
        audioData[i] = (float) ((mPhase - kPi) / kPi) * mAmplitude;
        mPhase += mPhaseIncrement;
        if (mPhase > kTwoPi) mPhase -= kTwoPi;
    }

    envelope->render(audioData, numFrames);
}

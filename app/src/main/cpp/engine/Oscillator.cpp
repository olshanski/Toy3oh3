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

    if (!envelope->isWaveOn()) {
        mPhase = 0.0;
        return;
    }

    for (int i = 0; i < numFrames; ++i) {
        if (!envelope->isWaveOn()) {
            audioData[i] = 0.0;
        } else {
            //audioData[i] = sinf(mPhase) * mAmplitude;
            audioData[i] = (float) ((mPhase - kPi) / kPi) * mAmplitude;
            mPhase += mPhaseIncrement;
            if (mPhase > kTwoPi) mPhase -= kTwoPi;
        }

        audioData[i] *= envelope->renderFrame();
    }
}

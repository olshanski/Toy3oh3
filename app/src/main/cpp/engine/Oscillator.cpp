//
// Created by Mikhail Olshanskii on 15.10.2021.
//

#include "Oscillator.h"
#include "android/log.h"

void Oscillator::render(float *audioData, int32_t numFrames) {

    if (!isWaveOn_.load()) mPhase = 0.0;

    for (int i = 0; i < numFrames; ++i) {
        if (isWaveOn_.load()) {
            audioData[i] = sinf(mPhase) * mAmplitude;
            mPhase += mPhaseIncrement;
            if (mPhase > kTwoPi) mPhase -= kTwoPi;
        } else {
            audioData[i] = 0.0;
        }
    }
}
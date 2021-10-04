//
// Created by Mikhail Olshanskii on 04.10.2021.
//

#include "Toy303Callback.h"

oboe::DataCallbackResult Toy303Callback::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    auto *output_data = static_cast<float *>(audioData);

    for (int i = 0; i < numFrames; ++i) {
        output_data[i] = sinf(mPhase) * mAmplitude;

        mPhase += mPhaseIncrement;
        if (mPhase > kTwoPi) mPhase -= kTwoPi;
    }

    return oboe::DataCallbackResult::Continue;
}

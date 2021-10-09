//
// Created by Mikhail Olshanskii on 04.10.2021.
//

#include "Toy303Callback.h"
#include <android/log.h>

Toy303Callback::Toy303Callback() {
    __android_log_print(ANDROID_LOG_ERROR, "Callback", "Initialized callback");
}

oboe::DataCallbackResult Toy303Callback::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    auto *output_data = static_cast<float *>(audioData);

    if (!isWaveOn_.load()) mPhase = 0;

    for (int i = 0; i < numFrames; ++i) {
        if (isWaveOn_.load()) {

            output_data[i] = sinf(mPhase) * mAmplitude;

            mPhase += mPhaseIncrement;
            if (mPhase > kTwoPi) mPhase -= kTwoPi;
        } else {
            output_data[i] = 0.0;
        }
    }

    return oboe::DataCallbackResult::Continue;
}

void Toy303Callback::onNoteSelected(int note, int octave) {
    isWaveOn_.store(true);
    updateNote(note, octave);
}

void Toy303Callback::onNoteReleased() {
    isWaveOn_.store(false);
}

void Toy303Callback::updateNote(int note, int octave) {
    int semiTones = kSemitonesPerOctave;

    if (octave <= 1) {
        semiTones += note;
    } else {
        semiTones += note + (octave - 1) * kSemitonesPerOctave ;
    }

    mPhaseIncrement.store((kTwoPi * calculateNoteFrequency(semiTones)) / static_cast<double>(kDefaultSampleRate));
}

double Toy303Callback::calculateNoteFrequency(int semitoneOffset) {
    // Formula taken from wikipedia
    return pow(2, (double)(semitoneOffset - kNoteA4Index) / (double) kSemitonesPerOctave) * kNoteA4FreqHz;
}

void Toy303Callback::changeVolume(double volume) {
    mAmplitude.store(volume);
}



//
// Created by Mikhail Olshanskii on 04.10.2021.
//

#include "Voice.h"
#include <android/log.h>

Voice::Voice() {
    mOscillator = std::make_unique<Oscillator>();
    __android_log_print(ANDROID_LOG_DEBUG, "Callback", "Initialized callback");
}

oboe::DataCallbackResult
Voice::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    auto *output_data = static_cast<float *>(audioData);
    mOscillator->render(output_data, numFrames);
    return oboe::DataCallbackResult::Continue;
}

void Voice::onNoteSelected(int note, int octave) {
    isWaveOn_.store(true);
    mOscillator->setWaveOn(true);
    updateNote(note, octave);
}

void Voice::onNoteReleased() {
    isWaveOn_.store(false);
    mOscillator->setWaveOn(false);
}

void Voice::updateNote(int note, int octave) {
    int semiTones = kSemitonesPerOctave;

    if (octave <= 1) {
        semiTones += note;
    } else {
        semiTones += note + (octave - 1) * kSemitonesPerOctave;
    }

    double frequency = calculateNoteFrequency(semiTones);
    mOscillator->setFrequency(frequency);
}

double Voice::calculateNoteFrequency(int semitoneOffset) {
    // Formula taken from wikipedia
    return pow(2, (double) (semitoneOffset - kNoteA4Index) / (double) kSemitonesPerOctave) *
           kNoteA4FreqHz;
}

void Voice::changeVolume(double volume) {
    mAmplitude.store(volume);
}



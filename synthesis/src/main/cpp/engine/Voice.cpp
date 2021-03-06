//
// Created by Mikhail Olshanskii on 04.10.2021.
//

#include "Voice.h"
#include <android/log.h>

Voice::Voice() {
    mOscillator = std::make_unique<Oscillator>();
    mEnvelope = std::make_unique<Envelope>();
    mEnvelope->setListener(this);
    mFilter = std::make_unique<Filter>();
    __android_log_print(ANDROID_LOG_DEBUG, "Callback", "Initialized callback");
}

oboe::DataCallbackResult Voice::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    auto *output_data = static_cast<float *>(audioData);

    if (mEnvelope->getPhase() == IDLE) {
        for (int i = 0; i < numFrames; i++) {
            output_data[i] = 0.0;
        }

        return oboe::DataCallbackResult::Continue;
    }

    for (int i = 0; i < numFrames; i++) {
        output_data[i] = mFilter->nextSample(mOscillator->nexSample() * mEnvelope->nextSample());
    }

    return oboe::DataCallbackResult::Continue;
}

void Voice::onNoteSelected(int note, int octave) {
    mEnvelope->enterPhase(ATTACK);
    updateNote(note, octave);
}

void Voice::onNoteReleased() {
    mEnvelope->enterPhase(RELEASE);
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

void Voice::setPhaseLength(int lengthMillis, Phase phase) {
    mEnvelope->setPhaseLength(lengthMillis, phase);
}

void Voice::setSustainLevel(double sustain) {
    mEnvelope->setSustainLevel(sustain);
}

void Voice::setWaveform(WaveForm waveForm) {
    mOscillator->setWaveForm(waveForm);
}

void Voice::setCutoffFrequency(int frequencyHz) {
    mFilter->setCutoffFrequency(frequencyHz);
}

void Voice::setFilterQ(double q) {
    mFilter->setQ(q);
}

void Voice::onEnvelopeStarted() {
    mOscillator->setWaveOn(true);
}

void Voice::onEnvelopeStopped() {
    mOscillator->setWaveOn(false);
}


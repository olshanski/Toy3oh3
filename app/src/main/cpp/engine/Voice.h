//
// Created by Mikhail Olshanskii on 04.10.2021.
//

#ifndef TOY3OH3_VOICE_H
#define TOY3OH3_VOICE_H

#include <oboe/Oboe.h>
#include "Oscillator.h"

class Voice : public oboe::AudioStreamDataCallback {
public:

    Voice();

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames);

    void onNoteSelected(int note, int octave);

    void onNoteReleased();

    void changeVolume(double volume);

    void setPhaseLength(int lengthMillis, Phase phase);

    void setSustainLevel(double sustain);

    void setWaveform(WaveForm waveForm);

private:
    static constexpr int kNoteA4Index = 49;
    static constexpr int kSemitonesPerOctave = 12;
    // A4
    static constexpr double kNoteA4FreqHz = 440.00;

    std::atomic<float> mAmplitude{0.2};
    std::atomic<bool> isWaveOn_{false};

    std::unique_ptr<Oscillator> mOscillator;

    std::unique_ptr<Envelope> mEnvelope;

    /**
     *
     * @param semitoneOffset note's offset in semitones from start of a piano keyboard.
     * Considering for A4 the offset is 49;
     * @return
     */
    static double calculateNoteFrequency(int semitoneOffset);

    void updateNote(int note, int octave);
};

#endif //TOY3OH3_VOICE_H

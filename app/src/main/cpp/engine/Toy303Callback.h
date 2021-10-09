//
// Created by Mikhail Olshanskii on 04.10.2021.
//

#ifndef TOY3OH3_TOY303CALLBACK_H
#define TOY3OH3_TOY303CALLBACK_H

#include <oboe/Oboe.h>
//Basic data callback that generates a sine wave
class Toy303Callback : public oboe::AudioStreamDataCallback {
public:

    Toy303Callback();

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames);

    void onNoteSelected(int note, int octave);

private:
    static  constexpr double kPi = M_PI;
    static constexpr double kTwoPi = kPi * 2;

    static constexpr int kNoteA4Index = 49;
    static constexpr int kSemitonesPerOctave = 12;

    // A4
    static constexpr double kNoteA4FreqHz = 440.00;

    static constexpr int kDefaultSampleRate = 48000;

    float mPhase = 0.0;

    std::atomic<float> mAmplitude{0.2};
    std::atomic<double> mPhaseIncrement{(kTwoPi * kNoteA4FreqHz) / static_cast<double>(kDefaultSampleRate)};

    /**
     *
     * @param semitoneOffset note's offset in semitones from start of a piano keyboard.
     * Considering for A4 the offset is 49;
     * @return
     */
    static double calculateNoteFrequency(int semitoneOffset);

    void updateNote(int note, int octave);
};

#endif //TOY3OH3_TOY303CALLBACK_H

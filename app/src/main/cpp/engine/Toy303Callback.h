//
// Created by Mikhail Olshanskii on 04.10.2021.
//

#ifndef TOY3OH3_TOY303CALLBACK_H
#define TOY3OH3_TOY303CALLBACK_H


#include <oboe/Oboe.h>

//Basic data callback that generates a sine wave
class Toy303Callback : public oboe::AudioStreamDataCallback {
public:

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames);

private:
    static const constexpr double kPi = M_PI;
    static const constexpr double kTwoPi = kPi * 2;

    // C3
    static const constexpr double kNoteA4Hz = 261.6256;

    float mPhase = 0.0;

    std::atomic<float> mAmplitude{0.2};
    std::atomic<double> mPhaseIncrement{(kTwoPi * kNoteA4Hz) / static_cast<double>(44100)};

};

#endif //TOY3OH3_TOY303CALLBACK_H

//
// Created by Mikhail Olshanskii on 03.10.2021.
//

#include "Toy303AudioEngine.h"
#include <android/log.h>
#include <oboe/Oboe.h>

const char *TAG = "Toy303AudioEngine";

//Basic data callback that generates a sine wave
class Toy303Callback : public oboe::AudioStreamDataCallback {
public:
    ~Toy303Callback() = default;

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override {
        auto *output_data = static_cast<float *>(audioData);

        for (int i = 0; i < numFrames; ++i) {
            output_data[i] = sinf(mPhase) * mAmplitude;

            mPhase += mPhaseIncrement;
            if (mPhase > kTwoPi) mPhase -= kTwoPi;
        }

        return oboe::DataCallbackResult::Continue;
    }

private:
    static const constexpr double kPi = M_PI;
    static const constexpr double kTwoPi = kPi * 2;
    static const constexpr double kNoteA4Hz = 440.0;

    float mPhase = 0.0;

    std::atomic<float> mAmplitude { 0.2 };
    std::atomic<double> mPhaseIncrement { (kTwoPi * kNoteA4Hz) / static_cast<double>(44100) };

};

Toy303Callback *toy303Callback = new Toy303Callback();

Toy303AudioEngine::Toy303AudioEngine() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Created audio engine");
}

oboe::Result Toy303AudioEngine::startEngine() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Starting audio engine");

    oboe::AudioStreamBuilder builder = oboe::AudioStreamBuilder();

    builder.setDirection(oboe::Direction::Output)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setSharingMode(oboe::SharingMode::Exclusive)
            ->setFormat(oboe::AudioFormat::Float)
            ->setChannelCount(oboe::ChannelCount::Mono)
            ->setDataCallback(toy303Callback);

    oboe::Result result = builder.openStream(mStream);

    oboe::AudioFormat format = mStream->getFormat();

    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Error %s", oboe::convertToText(result));
    } else {
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "AudioStream format is %s", oboe::convertToText(format));
    }

    return result;
}

oboe::Result Toy303AudioEngine::stopEngine() {
    oboe::Result result = oboe::Result::OK;
    mStream->close();
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Stopping audio engine");
    return result;
}

void Toy303AudioEngine::beep(bool isBeepOn) {
    if (isBeepOn) {
        mStream->requestStart();
    } else {
        mStream->requestStop();
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Beeping %d", isBeepOn);
}
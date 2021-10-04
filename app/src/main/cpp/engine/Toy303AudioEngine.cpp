//
// Created by Mikhail Olshanskii on 03.10.2021.
//

#include "Toy303AudioEngine.h"
#include <android/log.h>
#include <oboe/Oboe.h>

const char *TAG = "Toy303AudioEngine";

Toy303AudioEngine::Toy303AudioEngine() {
    toy303Callback = new Toy303Callback();

    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Created audio engine");
}

oboe::Result Toy303AudioEngine::startEngine() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Starting audio engine");

    oboe::Result result = openPlaybackStream();

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

oboe::Result Toy303AudioEngine::openPlaybackStream() {
    oboe::AudioStreamBuilder builder = oboe::AudioStreamBuilder();

    builder.setDirection(oboe::Direction::Output)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setSharingMode(oboe::SharingMode::Exclusive)
            ->setFormat(oboe::AudioFormat::Float)
            ->setChannelCount(oboe::ChannelCount::Mono)
            ->setDataCallback(toy303Callback);

    oboe::Result result = builder.openStream(mStream);

    return result;
}

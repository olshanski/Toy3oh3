//
// Created by Mikhail Olshanskii on 03.10.2021.
//

#include "Toy303AudioEngine.h"
#include <android/log.h>
#include <oboe/Oboe.h>

const char *TAG = "Toy303AudioEngine";

Toy303AudioEngine::Toy303AudioEngine() {
    toy303Callback = std::make_unique<Voice>();

    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Created audio engine");
}

oboe::Result Toy303AudioEngine::startEngine() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Starting audio engine");

    oboe::Result result = openPlaybackStream();

    oboe::AudioFormat format = mStream->getFormat();

    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Error %s", oboe::convertToText(result));
    } else {
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "AudioStream format is %s, sample rate: %d",
                            oboe::convertToText(format), mStream->getSampleRate());
    }

    mStream->requestStart();

    return result;
}

oboe::Result Toy303AudioEngine::stopEngine() {
    mStream->requestStop();
    oboe::Result result = mStream->close();
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Stopping audio engine");
    return result;
}

oboe::Result Toy303AudioEngine::openPlaybackStream() {
    oboe::AudioStreamBuilder builder = oboe::AudioStreamBuilder();

    builder.setDirection(oboe::Direction::Output)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setSharingMode(oboe::SharingMode::Exclusive)
            ->setFormat(oboe::AudioFormat::Float)
            ->setChannelCount(oboe::ChannelCount::Mono)
            ->setDataCallback(toy303Callback.get());

    oboe::Result result = builder.openStream(mStream);

    return result;
}

void Toy303AudioEngine::releaseNote() {
    toy303Callback->onNoteReleased();
}

void Toy303AudioEngine::playNote(int note, int octave) {
    toy303Callback->onNoteSelected(note, octave);
}

void Toy303AudioEngine::setVolume(double volume) {
    if (volume > 1.0 || volume < 0.0) {
        return;
    }

    toy303Callback->changeVolume(volume);
}

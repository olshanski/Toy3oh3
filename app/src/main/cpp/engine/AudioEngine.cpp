//
// Created by Mikhail Olshanskii on 03.10.2021.
//

#include "AudioEngine.h"
#include <android/log.h>

const char *TAG = "AudioEngine";

void AudioEngine::startEngine() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Starting audio engine");
}

void AudioEngine::stopEngine() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Stopping audio engine");
}

void AudioEngine::beep() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Beeping");
}
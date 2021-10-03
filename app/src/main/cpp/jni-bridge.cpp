#include <jni.h>
#include <string>

#include "engine/AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

extern "C" JNIEXPORT jstring JNICALL
Java_com_olshanski_toy3oh3_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"

JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_startAudioEngine(JNIEnv *env, jobject thiz) {
    audioEngine->startEngine();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_stopAudioEngine(JNIEnv *env, jobject thiz) {
    audioEngine->stopEngine();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_beep(JNIEnv *env, jobject thiz) {
    audioEngine->beep();
}
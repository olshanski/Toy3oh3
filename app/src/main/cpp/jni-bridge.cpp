#include <jni.h>
#include <string>

#include "engine/Toy303AudioEngine.h"

static Toy303AudioEngine *audioEngine = new Toy303AudioEngine();

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
Java_com_olshanski_toy3oh3_MainActivity_beep(JNIEnv *env, jobject thiz, jboolean isKeyDown) {
    audioEngine->beep(isKeyDown);
}
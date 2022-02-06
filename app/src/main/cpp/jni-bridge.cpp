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
Java_com_olshanski_toy3oh3_MainActivity_playNote(JNIEnv *env, jobject thiz, jint note,jint octave) {
    audioEngine->playNote(note, octave);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_releaseNote(JNIEnv *env, jobject thiz) {
    audioEngine->releaseNote();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setVolume(JNIEnv *env, jobject thiz, jdouble volume) {
    audioEngine->setVolume(volume);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setAttack(JNIEnv *env, jobject thiz, jint attack_millis) {
    audioEngine->setPhaseLength(attack_millis, ATTACK);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setDecay(JNIEnv *env, jobject thiz, jint decay_millis) {
    audioEngine->setPhaseLength(decay_millis, DECAY);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setRelease(JNIEnv *env, jobject thiz, jint release_millis) {
    audioEngine->setPhaseLength(release_millis, RELEASE);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setSustain(JNIEnv *env, jobject thiz, jdouble sustain) {
    audioEngine->setSustainLevel(sustain);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setWaveform(JNIEnv *env, jobject thiz, jint waveform) {
    if (waveform == 0) {
        audioEngine->setWaveform(SAWTOOTH);
    } else if (waveform == 1) {
        audioEngine->setWaveform(PULSE);
    } else {
        audioEngine->setWaveform(SINE);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setCutoffFrequency(JNIEnv *env, jobject thiz,
                                                           jint frequency_hz) {
    audioEngine->setCutoffFrequency(frequency_hz);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_MainActivity_setQ(JNIEnv *env, jobject thiz, jdouble q) {
    audioEngine->setFilterQ(q);
}
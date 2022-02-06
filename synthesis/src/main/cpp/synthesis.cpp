#include <jni.h>
#include <string>

#include "engine/Toy303AudioEngine.h"

std::unique_ptr<Toy303AudioEngine> engine = std::make_unique<Toy303AudioEngine>();

extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_startAudioEngine(JNIEnv *env, jobject thiz) {
    engine->startEngine();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_stopAudioEngine(JNIEnv *env, jobject thiz) {
    engine->stopEngine();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_playNote(JNIEnv *env, jobject thiz, jint note,
                                                        jint octave) {
    engine->playNote(note, octave);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_releaseNote(JNIEnv *env, jobject thiz) {
    engine->releaseNote();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setVolume(JNIEnv *env, jobject thiz,
                                                         jdouble volume) {
    engine->setVolume(volume);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setAttack(JNIEnv *env, jobject thiz,
                                                         jint attack_millis) {
    engine->setPhaseLength(attack_millis, ATTACK);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setDecay(JNIEnv *env, jobject thiz,
                                                        jint decay_millis) {
    engine->setPhaseLength(decay_millis, DECAY);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setRelease(JNIEnv *env, jobject thiz,
                                                          jint release_millis) {
    engine->setPhaseLength(release_millis, RELEASE);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setSustain(JNIEnv *env, jobject thiz,
                                                          jdouble sustain) {
    engine->setSustainLevel(sustain);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setWaveform(JNIEnv *env, jobject thiz,
                                                           jint waveform) {
    if (waveform == 0) {
        engine->setWaveform(SAWTOOTH);
    } else if (waveform == 1) {
        engine->setWaveform(PULSE);
    } else {
        engine->setWaveform(SINE);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setCutoffFrequency(JNIEnv *env, jobject thiz,
                                                                  jint frequency_hz) {
    engine->setCutoffFrequency(frequency_hz);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_olshanski_toy3oh3_synthesis_Synthesis_setQ(JNIEnv *env, jobject thiz, jdouble q) {
    engine->setFilterQ(q);
}
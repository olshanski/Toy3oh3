//
// Created by Mikhail Olshanskii on 16.10.2021.
//

#ifndef TOY3OH3_ENVELOPE_H
#define TOY3OH3_ENVELOPE_H

#include <oboe/Oboe.h>
#include "atomic"
#include "math.h"
#include "android/log.h"

static constexpr int kDefaultSampleRate = 48000;

static constexpr int kDefaultDurationMs = 500;
static constexpr int kMsPerS = 1000;

static constexpr int kPhaseDurationFrames = kDefaultSampleRate / 2;
static constexpr float kAmplitudeDeltaPerFrame = (1.0 / (float) kDefaultSampleRate) * (kMsPerS / kDefaultDurationMs);
static constexpr float kDefaultSustain = 1.0;

enum Phase {
    ATTACK, DECAY, SUSTAIN, RELEASE
};

class Envelope {

public:

    void render(float *audioData, int32_t numFrames) {
        for (int i = 0; i < numFrames; ++i) {
            switch (mPhase) {
                case ATTACK:
                    if (mCurrentFrame - mLastEventFrame >= kPhaseDurationFrames) {
                        mAmplitude.store(kDefaultSustain);
                        audioData[i] *= kDefaultSustain;
                        mPhase = SUSTAIN;
                    } else {
                        mAmplitude.store(std::min(mAmplitude.load() + kAmplitudeDeltaPerFrame, (float) 1.0));
                        audioData[i] *= mAmplitude;
                    }
                    break;
                case DECAY:
                    // NO OP FOR NOW
                    break;
                case SUSTAIN:
                    audioData[i] *= mAmplitude;
                    break;
                case RELEASE:
                    if (mCurrentFrame - mLastEventFrame >= kPhaseDurationFrames) {
                        mAmplitude.store(0.0);
                        audioData[i] *= 0.0;
                    } else {
                        mAmplitude.store(std::max((mAmplitude.load() - kAmplitudeDeltaPerFrame), (float) 0.0));
                        audioData[i] *= mAmplitude;
                    }
                    break;
            }

            mCurrentFrame++;
        }
    }

    void setWaveOn(bool isWaveOn) {
        isWaveOn_.store(isWaveOn);
    };

    void keyPressed() {
        mPhase.store(ATTACK);
        mAmplitude.store(0.0);
        mLastEventFrame.store(mCurrentFrame.load());
    }

    void keyReleased() {
        mLastEventFrame.store(mCurrentFrame.load());
        mPhase.store(RELEASE);
    }

private:
    std::atomic<Phase> mPhase{ATTACK};

    std::atomic<int32_t> mCurrentFrame{0};
    std::atomic<float> mAmplitude {0.0};
    std::atomic<int> mLastEventFrame{ -1};

    std::atomic<bool> isWaveOn_{false};

};

#endif //TOY3OH3_ENVELOPE_H

//
// Created by Mikhail Olshanskii on 16.10.2021.
//

#ifndef TOY3OH3_ENVELOPE_H
#define TOY3OH3_ENVELOPE_H

#include <oboe/Oboe.h>
#include "atomic"
#include "math.h"
#include "android/log.h"

//TODO: Cleanup

static constexpr int kDefaultSampleRate = 48000;

// 500ms
static constexpr int kDefaultAttackInFrames = 24000;
// 500ms
static constexpr int kDefaultDecayInFrames = 24000;
static constexpr float kDefaultSustain = 0.2;
// 500ms
static constexpr int kDefaultReleaseInFrames = 24000;

static constexpr float kAmplitudeDeltaPerFrameAttack = (1.0) / (float) kDefaultAttackInFrames;
static constexpr float kAmplitudeDeltaPerFrameDecay = (0.8) / (float ) kDefaultDecayInFrames;
static constexpr float kAmplitudeDeltaPerFrameRelease = (1.0 + (kDefaultSustain - 1.0)) / (float ) kDefaultReleaseInFrames;


enum Phase {
    ATTACK, DECAY, SUSTAIN, RELEASE, IDLE
};

class Envelope {

public:

    float renderFrame() {
        switch (mPhase) {
            case ATTACK:
                if (mCurrentFrame - mLastEventFrame >= kDefaultAttackInFrames) {
                    mLastEventFrame.store(mCurrentFrame);
                    if (1.0 == mSustainLevel) {
                        mPhase = SUSTAIN;
                    } else {
                        float decayToGo = 1.0 - kDefaultSustain;
                        mDecayDeltaPerFrame = decayToGo / kDefaultDecayInFrames;
                        mPhase = DECAY;
                    }
                } else {
                    mAmplitude.store(std::min(mAmplitude.load() + kAmplitudeDeltaPerFrameAttack,
                                              (float) 1.0));
                }
                break;
            case DECAY:
                if (mCurrentFrame - mLastEventFrame >= mDecayInFrames) {
                    mPhase = SUSTAIN;
                } else {
                    mAmplitude.store(
                            std::max(mAmplitude.load() - mDecayDeltaPerFrame, mSustainLevel));
                }
                break;
            case SUSTAIN:
                break;
            case RELEASE:
                if (mCurrentFrame - mLastEventFrame >= mReleaseInFrames) {
                    mAmplitude.store(0.0);
                    mPhase = IDLE;
                } else {
                    mAmplitude.store(
                            std::max((mAmplitude.load() - mReleaseDeltaPerFrame), (float) 0.0));
                }
                break;
            case IDLE:
                break;
        }

        mCurrentFrame++;
        return mAmplitude.load();
    }

    bool isWaveOn() {
        return mPhase.load() != IDLE;
    }

    void keyPressed() {
        mPhase.store(ATTACK);
        mCurrentFrame.store(0);
        mLastEventFrame.store(0);
    }

    void keyReleased() {
        // ugly
        if (!isWaveOn()) {
            return;
        }

        mReleaseDeltaPerFrame = mAmplitude / kDefaultReleaseInFrames;
        mPhase.store(RELEASE);
        mLastEventFrame.store(mCurrentFrame.load());
    }

private:
    std::atomic<Phase> mPhase{IDLE};

    std::atomic<int32_t> mCurrentFrame{0};
    std::atomic<float> mAmplitude {0.0};
    std::atomic<int> mLastEventFrame{ -1};

    float mReleaseInFrames = kDefaultReleaseInFrames;
    float mDecayInFrames = kDefaultDecayInFrames;

    float mReleaseDeltaPerFrame = kAmplitudeDeltaPerFrameRelease;
    float mDecayDeltaPerFrame = kAmplitudeDeltaPerFrameDecay;
    float mSustainLevel = kDefaultSustain;

};

#endif //TOY3OH3_ENVELOPE_H

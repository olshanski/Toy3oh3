//
// Created by Mikhail Olshanskii on 16.10.2021.
//

#ifndef TOY3OH3_ENVELOPE_H
#define TOY3OH3_ENVELOPE_H

#include <oboe/Oboe.h>
#include "atomic"
#include "math.h"
#include "android/log.h"
#include <string>
#include <string_view>

//TODO: Cleanup

static constexpr int kDefaultSampleRate = 48000;

// 500ms
static constexpr int kDefaultAttackInFrames = 24000;
// 500ms
static constexpr int kDefaultDecayInFrames = 24000;
static constexpr float kDefaultSustain = 0.2;
// 500ms
static constexpr int kDefaultReleaseInFrames = 48000;

enum Phase {
    IDLE = 0,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE,
    kNumEnvelopePhases
};

class Envelope {

public:

    float renderFrame();
    void enterPhase(Phase phase);

    inline Phase getPhase() const { return mPhase; };

private:
    Phase mPhase = IDLE;
    int mCurrentSample = 0;
    int mNextPhaseSample = kDefaultAttackInFrames;
    int mLastEventSample = 0;
    int sampleRate = 480000;
    double mLevel = 0.0;
    double multiplier;

    void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
};

#endif //TOY3OH3_ENVELOPE_H

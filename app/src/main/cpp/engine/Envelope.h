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

static constexpr int kDefaultAttackMillis = 500;
static constexpr int kDefaultDecayMillis = 2500;
static constexpr int kDefaultReleaseMillis = 500;

static constexpr float kDefaultSustain = 0.2;
static constexpr float kMinimumLevel = 0.001;

enum Phase {
    IDLE = 0,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE,
    kNumPhases
};

class Envelope {

public:

    float nextSample();
    void enterPhase(Phase phase);
    void setSampleRate(int newSampleRate);
    void setSustainLevel(double sustain);
    void setPhaseLength(int millis, Phase phase);
    inline Phase getPhase() const { return mPhase; };

    Envelope();
private:
    Phase mPhase = IDLE;

    int mCurrentSample = 0;
    int mNextPhaseSample = kDefaultAttackMillis;
    int mSampleRate = kDefaultSampleRate;

    double mLevel = 0.0;
    double multiplier;

    double mSustain = kDefaultSustain;

    int mPhaseLengths[kNumPhases];

    void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);

    int millisToSamples(int millis) const;
};

#endif //TOY3OH3_ENVELOPE_H

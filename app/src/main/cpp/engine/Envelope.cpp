//
// Created by Mikhail Olshanskii on 16.10.2021.
//

#include "Envelope.h"

Envelope::Envelope() {
    mPhaseLengths[IDLE] = 0;
    mPhaseLengths[ATTACK] = kDefaultAttackMillis;
    mPhaseLengths[DECAY] = kDefaultDecayMillis;
    mPhaseLengths[SUSTAIN] = 0;
    mPhaseLengths[RELEASE] = kDefaultReleaseMillis;
}

void Envelope::enterPhase(Phase phase) {
    mPhase = phase;
    mCurrentSample = 0;

    mNextPhaseSample = millisToSamples(mPhaseLengths[phase]);

    switch (phase) {
        case IDLE:
            mLevel = 0.0;
            multiplier = 1.0;
            break;
        case ATTACK:
            mLevel = kMinimumLevel;
            calculateMultiplier(mLevel, 1.0, mNextPhaseSample);
            break;
        case DECAY:
            mLevel = 1.0;
            calculateMultiplier(mLevel, fmax(mSustain, kMinimumLevel), mNextPhaseSample);
            break;
        case SUSTAIN:
            mLevel = mSustain;
            multiplier = 1.0;
            break;
        case RELEASE:
            calculateMultiplier(mLevel, kMinimumLevel, mNextPhaseSample);
            break;
        default:
            break;
    }
}

float Envelope::nextSample() {
    if (mPhase != IDLE && mPhase != SUSTAIN) {
        if (mCurrentSample == mNextPhaseSample) {
            auto newPhase = static_cast<Phase>((mPhase + 1) % kNumPhases);
            enterPhase(newPhase);
        }

        mLevel *= multiplier;
        mCurrentSample++;
    }

    return mLevel;
}

void Envelope::setSampleRate(int newSampleRate) {
    mSampleRate = newSampleRate;
}

void Envelope::setPhaseLength(int millis, Phase phase) {
    mPhaseLengths[phase] = millis;

    if (mPhase == phase) {
        if (mPhase == SUSTAIN || mPhase == IDLE) {
            return;
        }

        double targetLevel;

        switch (mPhase) {
            case ATTACK:
                targetLevel = 1;
                break;
            case DECAY:
                targetLevel = fmax(kMinimumLevel, mSustain);
                break;
            case RELEASE:
                targetLevel = kMinimumLevel;
                break;
            default:
                return;
        }

        double currentPhaseProgress = (mCurrentSample + 0.0) / mNextPhaseSample;
        double remainingProgress = 1.0 - currentPhaseProgress;

        int samplesToGo = millisToSamples(millis) * remainingProgress;
        mNextPhaseSample = mCurrentSample + samplesToGo;
        calculateMultiplier(mLevel, targetLevel, samplesToGo);
    }
}


void Envelope::setSustainLevel(double sustain) {
    mSustain = sustain;

    if (mPhase == DECAY) {
        int samplesToGo = mNextPhaseSample - mCurrentSample;
        calculateMultiplier(mLevel, fmax(mSustain, kMinimumLevel), samplesToGo);
    } else if (mPhase == SUSTAIN) {
        mLevel = sustain;
    }
}

void Envelope::calculateMultiplier(double startLevel, double endLevel,
                                   unsigned long long lengthInSamples) {
    multiplier = 1.0 + (log(endLevel) - log(startLevel)) / (lengthInSamples);
}

int Envelope::millisToSamples(int millis) const {
    return (float) millis / 1000.0 * mSampleRate;
}
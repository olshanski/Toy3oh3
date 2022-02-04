//
// Created by Mikhail Olshanskii on 16.10.2021.
//

#include "Envelope.h"

void Envelope::enterPhase(Phase phase) {
    mPhase = phase;
    mCurrentSample = 0;

    if (mPhase == IDLE || mPhase == SUSTAIN) {
        mNextPhaseSample = 0;
    } else {
        switch (mPhase) {
            case ATTACK:
                mNextPhaseSample = kDefaultAttackInFrames;
                break;
            case DECAY:
                mNextPhaseSample = kDefaultDecayInFrames;
                break;
            case RELEASE:
                mNextPhaseSample = kDefaultReleaseInFrames;
                break;
            default:
                break;
        }
    }

    switch (phase) {
        case IDLE:
            mLevel = 0.0;
            multiplier = 1.0;
            break;
        case ATTACK:
            mLevel = 0.01;
            calculateMultiplier(mLevel, 1.0, mNextPhaseSample);
            break;
        case DECAY:
            mLevel = 1.0;
            calculateMultiplier(mLevel, fmax(0.5, 0.01), mNextPhaseSample);
            break;
        case SUSTAIN:
            mLevel = 0.5;
            multiplier = 1.0;
            break;
        case RELEASE:
            calculateMultiplier(mLevel, 0.01, mNextPhaseSample);
            break;
        default:
            break;
    }
}

float Envelope::renderFrame() {
    if (mPhase != IDLE && mPhase != SUSTAIN) {
        if (mCurrentSample == mNextPhaseSample) {
            Phase newPhase;
            switch (mPhase) {
                case ATTACK:
                    newPhase = DECAY;
                    mNextPhaseSample = kDefaultDecayInFrames;

                    enterPhase(newPhase);
                    break;
                case DECAY:
                    newPhase = SUSTAIN;

                    enterPhase(newPhase);
                    break;
                case RELEASE:
                    newPhase = IDLE;
                    mNextPhaseSample = kDefaultAttackInFrames;
                    enterPhase(newPhase);
                    mLevel = 0.01;
                default:
                    break;
            }
        }

        mLevel *= multiplier;
        mCurrentSample++;
    }

    return mLevel;
}

void Envelope::calculateMultiplier(double startLevel, double endLevel,
                                   unsigned long long lengthInSamples) {
    multiplier = 1.0 + (log(endLevel) - log(startLevel)) / (lengthInSamples);
}
//
// Created by Mikhail Olshanskii on 05.10.2021.
//


#include "Filter.h"
#include <android/log.h>
#include <cmath>

const char *TAG = "Filter";

Filter::Filter() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Created filter %d", (getCutoffFrequency()));

    mQ = 3.0;
    mFrequencyCutoff = 440 / mSampleRate;
    z1 = z2 = 0.0;
    a0 = 1.0;
    a1 = a2 = b1 = b2 = 0.0;

    calcBiQuad();
}

double Filter::nextSample(double sample) {
    out = sample * a0 + z1;

    z1 = sample * a1 + z2 - b1 * out;
    z2 = sample * a2 - b2 * out;
    return out;
}

void Filter::setFilterType(FilterType filterType) {
    mFilterType = filterType;
    calcBiQuad();
}

void Filter::setCutoffFrequency(int frequencyCutoff) {
    mFrequencyCutoff = frequencyCutoff / mSampleRate;
    calcBiQuad();
}

void Filter::setQ(double q) {
    mQ = q;
    calcBiQuad();
}

void Filter::calcBiQuad() {
    double norm;
    double K = tan(M_PI * mFrequencyCutoff);

    switch (mFilterType) {

        case LOW_PASS:
            norm = 1 / (1 + K / mQ + K * K);
            a0 = K * K * norm;
            a1 = 2 * a0;
            a2 = a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / mQ + K * K) * norm;
            break;
        case HIGH_PASS:
            norm = 1 / (1 + K / mQ + K * K);
            a0 = 1 * norm;
            a1 = -2 * a0;
            a2 = a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / mQ + K * K) * norm;
            break;
        case BAND_PASS:
            norm = 1 / (1 + K / mQ + K * K);
            a0 = K / mQ * norm;
            a1 = 0;
            a2 = -a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / mQ + K * K) * norm;
            break;
        default:
            break;
    }
}

//
// Created by Mikhail Olshanskii on 05.10.2021.
//


#include "Filter.h"
#include <android/log.h>

const char *TAG = "Filter";

Filter::Filter() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Created filter %d", (getCutoffFrequency()));
}

double Filter::processSample(double sample) {
    // TODO implement a proper filter
    out = mCutoffFrequency * sample + (1 - mCutoffFrequency) * out;
    return out;
}

void Filter::setFilterType(FilterType filterType) {
    mFilterType = filterType;
}

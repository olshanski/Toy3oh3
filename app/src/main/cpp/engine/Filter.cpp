
#include "Filter.h"
#include <android/log.h>

const char *TAG = "Filter";

Filter::Filter() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Created filer");
}

double Filter::filter(double sample) {
    return sample;
}

void Filter::setFilterType(FilterType filterType) {
    mFilterType = filterType;
}

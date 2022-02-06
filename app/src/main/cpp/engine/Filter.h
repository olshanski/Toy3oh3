//
// Created by Mikhail Olshanskii on 05.10.2021.
//

#ifndef TOY3OH3_FILTER_H
#define TOY3OH3_FILTER_H

enum FilterType {
    LOW_PASS = 0,
    HIGH_PASS,
    BAND_PASS,
    kNumFilterTypes
};

class Filter {

public:

    Filter();

    void setCutoffFrequency(int frequencyCutoff);

    int getCutoffFrequency() {
        return  mCutoffFrequency * kDefaultSampleRate;
    };

    void setFilterType(FilterType filterType);

    FilterType getFilterType() {
        return mFilterType;
    }

    void setQ(double q);

    double nextSample(double sample);

private:
    static constexpr double kDefaultSampleRate = 48000.0;
    static constexpr int kDefaultFrequencyCutoffHz = 440;

    double mCutoffFrequency = kDefaultFrequencyCutoffHz / kDefaultSampleRate;
    FilterType mFilterType = LOW_PASS;
    double out = 0.0;
    double mFrequencyCutoff, mQ;
    double mSampleRate = kDefaultSampleRate;

    double a0, a1, a2, b1, b2;
    double z1, z2;

    void calcBiQuad();
};

#endif
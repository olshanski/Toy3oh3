//
// Created by Mikhail Olshanskii on 05.10.2021.
//

#ifndef TOY3OH3_FILTER_H
#define TOY3OH3_FILTER_H

enum FilterType {
    // TODO: add hipass, bandpass and notch processSample types
    LOW_PASS
};

class Filter {

public:

    Filter();

    inline void setCutoffFrequency(int cutoffFrequencyHz) {
        mCutoffFrequency = cutoffFrequencyHz / kDefaultCutoffFrequencyHz;
    };

    int getCutoffFrequency() {
        return  mCutoffFrequency * kDefaultCutoffFrequencyHz;
    };

    void setFilterType(FilterType filterType);

    double processSample(double sample);

private:
    static constexpr double kDefaultCutoffFrequencyHz = 22000.0;

    double mCutoffFrequency = kDefaultCutoffFrequencyHz / kDefaultCutoffFrequencyHz;
    FilterType mFilterType = LOW_PASS;

    double out = 0.0;
};

#endif
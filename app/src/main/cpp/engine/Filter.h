
#ifndef TOY3OH3_FILTER_H
#define TOY3OH3_FILTER_H

enum FilterType {
    // TODO: add hipass, bandpass and notch filter types
    LOW_PASS
};

class Filter {

public:

    Filter();

    inline void setCutoffFrequency(int cutoffFrequencyHz) {
        mCutoffFrequency = cutoffFrequencyHz;
    };

    int getCutoff() {
        return  mCutoffFrequency;
    };

    void setFilterType(FilterType filterType);

    double filter(double sample);

private:
    static constexpr int kDefaultCutoffFrequencyHz = 22000;

    int mCutoffFrequency = kDefaultCutoffFrequencyHz;
    FilterType mFilterType = LOW_PASS;
};

#endif
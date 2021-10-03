//
// Created by Mikhail Olshanskii on 03.10.2021.
//

#ifndef TOY3OH3_TOY303AUDIOENGINE_H
#define TOY3OH3_TOY303AUDIOENGINE_H

#include <oboe/Oboe.h>


class Toy303AudioEngine {
public:
    Toy303AudioEngine();

    oboe::Result startEngine();
    oboe::Result stopEngine();

    void beep(bool isBeepOn);

private:

    oboe::Result openPlaybackStream();

    std::shared_ptr<oboe::AudioStream> mStream;

    int32_t        mDeviceId = oboe::Unspecified;
    int32_t        mChannelCount = oboe::Unspecified;
    oboe::AudioApi mAudioApi = oboe::AudioApi::Unspecified;
    std::mutex     mLock;
};


#endif //TOY3OH3_TOY303AUDIOENGINE_H

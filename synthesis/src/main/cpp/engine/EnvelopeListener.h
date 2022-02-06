
#ifndef TOY3OH3_ENVELOPELISTENER_H
#define TOY3OH3_ENVELOPELISTENER_H

#include "Envelope.h"

class EnvelopeListener {
public:
    virtual void onEnvelopeStarted() = 0;
    virtual void onEnvelopeStopped() = 0;
};

#endif
//
// Created by Mikhail Olshanskii on 24.10.2021.
//

#ifndef TOY3OH3_CIRCULARBUFFER_H
#define TOY3OH3_CIRCULARBUFFER_H

#include "memory.h"

class CircularBuffer {

public:
    CircularBuffer(int size);

    ~CircularBuffer();

    int getSize();

    int getBufferLength();

    bool isEmpty();

    bool isFull();

    void enqueue(float sample) {
        _buffer[_tail] = sample;

        if (++_tail >= _bufferLength) {
            _tail = 0;
        }
    }

    float dequeue() {
        float item = _buffer[_head];

        if (++_head >= _bufferLength) {
            _head = 0;
        }

        return item;
    }

    float peek() {
        return _buffer[_head];
    }

    void flush() {
        _head = 0;
        _tail = 0;
        memset(_buffer, 0, _bufferLength * sizeof(float));
    }

private:

    float *_buffer;
    int _bufferLength;
    int _head;
    int _tail;
};


#endif //TOY3OH3_CIRCULARBUFFER_H

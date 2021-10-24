//
// Created by Mikhail Olshanskii on 24.10.2021.
//

#include "CircularBuffer.h"
#include "memory.h"

CircularBuffer::CircularBuffer(int size) {
    _bufferLength = size;
    _buffer = new float[size];
    memset(_buffer, 0, size * sizeof(float));
    _head = 0;
    _tail = 0;
}

CircularBuffer::~CircularBuffer() {
    delete[] _buffer;
    _buffer = nullptr;
}

int CircularBuffer::getBufferLength() {
    return _bufferLength;
}

int CircularBuffer::getSize() {
    return _tail - _head;
}

bool CircularBuffer::isEmpty() {
    return getSize() == 0;
}

bool CircularBuffer::isFull() {
    return getSize() == _bufferLength;
}




/*
  ==============================================================================

    RecirculatingBuffer.cpp
    Created: 9 Nov 2019 2:57:04pm
    Author:  Spenser Saling

  ==============================================================================
*/

#include "RecirculatingBuffer.h"

RecirculatingBuffer::RecirculatingBuffer(){
    
}
RecirculatingBuffer::~RecirculatingBuffer(){
    
}

void RecirculatingBuffer::zero(int size){
    buffer.setSize(1, size);
    buffer.clear();
    writeIndex = 0;
}

void RecirculatingBuffer::writeSample(float sample){
    buffer.setSample(0, writeIndex, sample);
    
    increment();
}

float RecirculatingBuffer::getSample(int offsetSamples){
    int readIndex = writeIndex - offsetSamples;
    if (readIndex < 0) {
        readIndex = buffer.getNumSamples() + readIndex;
    }
    return buffer.getSample(0, readIndex);
}

void RecirculatingBuffer::increment(){
    writeIndex += 1;
    writeIndex %= buffer.getNumSamples();
}

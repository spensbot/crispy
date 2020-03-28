/*
  ==============================================================================

    RecirculatingBuffer.h
    Created: 9 Nov 2019 2:57:04pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

//A recirculating AudioBuffer with a single channel
class RecirculatingBuffer {
public:
    
    RecirculatingBuffer();
    ~RecirculatingBuffer();
    
    void zero(int size);
    
    void writeSample(float sample);
    float getSample(int offsetSamples);
    
    AudioBuffer<float> buffer;
    
private:
    
    void increment();
    
    int writeIndex = 0;
    
};

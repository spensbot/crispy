/*
  ==============================================================================

    CrispySaturator.h
    Created: 5 Dec 2019 11:40:41am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class CrispySaturator
{
public:
    static float saturateSample(float sample, float squishFactor);
    
    static float saturateAngle(float angle, float squishFactor);
    
    static void saturate(AudioSampleBuffer& buffer, int startSample, int numSamples, float squishFactor);
    
private:
    
    
};

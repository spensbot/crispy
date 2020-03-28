/*
  ==============================================================================

    CrispySaturator.cpp
    Created: 5 Dec 2019 11:40:41am
    Author:  Spenser Saling

  ==============================================================================
*/

#include "CrispySaturator.h"

//Takes any value and clips it from -1 to 1. Values between this range are pushed outwards or pulled into the origin depending on squishFactor
float CrispySaturator::saturateSample(float sample, float squishFactor)
{
    
    if (sample > 1.0f) return 1.0f;
    if (sample < -1.0f) return -1.0f;
    
    if (sample > 0) {
        return 1.0f - powf(1.0f-sample, squishFactor);
    } else {
        return -(1.0f - powf(1.0f+sample, squishFactor));
    }
}

//Requires input between 0 and 2pi for efficiency.
//Applies the saturation above, using pi as the midpoint instead of 0.
float CrispySaturator::saturateAngle(float angle, float squishFactor)
{
    //first, scale the input to be between 0 and 2
    float x = angle/MathConstants<float>::pi;
    //then, shift values to be between -1 and 1;
    x -= 1;
    //saturate x
    float saturatedX = saturateSample(x, squishFactor);
    //convert the saturated value back to an angle
    float saturatedAngle = (saturatedX + 1) * MathConstants<float>::pi;
    return saturatedAngle;
}

void CrispySaturator::saturate(AudioSampleBuffer& buffer, int startSample, int numSamples, float squishFactor)
{
    for (int sample = startSample ; sample<startSample+numSamples ; sample++)
    {
        for (int channel = 0 ; channel<buffer.getNumChannels() ; channel++)
        {
            float currentSample = buffer.getSample(channel, sample);
            float saturatedSample = saturateSample(currentSample, squishFactor);
            buffer.setSample(channel, sample, saturatedSample);
        }
    }
}

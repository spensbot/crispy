/*
  ==============================================================================

    CrispySaturator.cpp
    Created: 5 Dec 2019 11:40:41am
    Author:  Spenser Saling

  ==============================================================================
*/

#include "CrispySaturator.h"
#include "DebugWindow.h"

float CrispySaturator::oddSaturate(float sample, float power)
{
    if (sample > 0) {
        return 1.0f - powf(1.0f-sample, power);
    } else {
        return -(1.0f - powf(1.0f+sample, power));
    }
}

float CrispySaturator::evenSaturate(float sample, float power, float mix)
{
    float wet = powf(sample, (int)power);
    wet = fabs(wet);
    wet -= 0.5f;
    wet *= 2.0f;
    return wet * mix + sample * (1.0f - mix);
}

float CrispySaturator::saturateSample(float sample, float oddPower, float evenPower, float evenMix)
{
    if (sample > 1.0f) return 1.0f;
    if (sample < -1.0f) return -1.0f;
    
    sample = oddSaturate(sample, oddPower);
    
    sample = evenSaturate(sample, evenPower, evenMix);
    
    return sample;
}

void CrispySaturator::saturate(AudioSampleBuffer& buffer, int startSample, int numSamples, float oddPower, int evenPower, float evenMix)
{
    for (int sample = startSample ; sample<startSample+numSamples ; sample++)
    {
        for (int channel = 0 ; channel<buffer.getNumChannels() ; channel++)
        {
            float currentSample = buffer.getSample(channel, sample);
            float saturatedSample = saturateSample(currentSample, oddPower, evenPower, evenMix);
            buffer.setSample(channel, sample, saturatedSample);
        }
    }
}

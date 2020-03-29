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

float CrispySaturator::evenSaturate(float sample, float mix, bool smooth)
{
    float wet = smooth ? sample * sample : fabs(sample);
    wet -= 0.5f;
    wet *= 2.0f;
    return wet * mix + sample * (1.0f - mix);
}

float CrispySaturator::saturateSample(float sample, float oddPower, float evenMix, bool evenSmooth)
{
    if (sample > 1.0f) return 1.0f;
    if (sample < -1.0f) return -1.0f;
    
    sample = oddSaturate(sample, oddPower);
    
    sample = evenSaturate(sample, evenMix, evenSmooth);
    
    return sample;
}

void CrispySaturator::saturate(AudioSampleBuffer& buffer, int startSample, int numSamples, float oddPower, float evenMix, bool evenSmooth)
{
    for (int sample = startSample ; sample<startSample+numSamples ; sample++)
    {
        for (int channel = 0 ; channel<buffer.getNumChannels() ; channel++)
        {
            float currentSample = buffer.getSample(channel, sample);
            float saturatedSample = saturateSample(currentSample, oddPower, evenMix, evenSmooth);
            buffer.setSample(channel, sample, saturatedSample);
        }
    }
}

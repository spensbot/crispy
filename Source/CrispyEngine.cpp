/*
  ==============================================================================

    CrispyEngine.cpp
    Created: 13 Dec 2019 2:24:38pm
    Author:  Spenser Saling

  ==============================================================================
*/

#include "CrispyEngine.h"

CrispyEngine::CrispyEngine(AudioProcessorValueTreeState& p)
: parameters(p)
{
    parameters.addParameterListener("inGain", this);
    parameters.addParameterListener("outGain", this);
    parameters.addParameterListener("saturation", this);

    inGainRamper.initialize(*parameters.getRawParameterValue("inGain"), 0.1);
    outGainRamper.initialize(*parameters.getRawParameterValue("outGain"), 0.1);
    saturationRamper.initialize(*parameters.getRawParameterValue("saturation"), 0.1);
    
    const int bufferSize = 100000;
    
    inBuffer.zero(bufferSize);
    outBuffer.zero(bufferSize);
}

void CrispyEngine::process(AudioBuffer<float> &buffer)
{
    for (auto sample = 0 ; sample < buffer.getNumSamples() ; sample++)
    {
        float inSample;
        float outSample;
        float inLevel = Decibels::decibelsToGain(inGainRamper.getNext());
        float saturation = saturationRamper.getNext();
        float outLevel = Decibels::decibelsToGain(outGainRamper.getNext());
        
        for (auto channel = 0 ; channel < buffer.getNumChannels() ; channel++)
        {
            //Get the current sample
            inSample = buffer.getSample(channel, sample);
            
            //Apply In Gain
            inSample *= inLevel;
            
            //Saturate the Sample
            outSample = CrispySaturator::saturateSample(inSample, saturation);
            
            //Apply Out Gain
            outSample *= outLevel;
            
            //Write modified sample to buffer
            buffer.setSample(channel, sample, outSample);
        }
        
        //Record the last channel's samples to the in and out buffers for viewing.
        inBuffer.writeSample(inSample);
        outBuffer.writeSample(outSample);
    }
}

void CrispyEngine::parameterChanged(const String& parameterID, float newValue )
{
    if (parameterID == "inGain") {
        inGainRamper.updateTarget(newValue);
    } else if (parameterID == "outGain") {
        outGainRamper.updateTarget(newValue);
    } else if (parameterID == "saturation") {
        saturationRamper.updateTarget(newValue);
    }
}

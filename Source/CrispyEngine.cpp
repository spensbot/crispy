/*
  ==============================================================================

    CrispyEngine.cpp
    Created: 13 Dec 2019 2:24:38pm
    Author:  Spenser Saling

  ==============================================================================
*/

#include "CrispyEngine.h"
#include "Constants.h"
#include "DebugWindow.h"

CrispyEngine::CrispyEngine(AudioProcessorValueTreeState& p)
: parameters(p)
{
    parameters.addParameterListener(Constants::ID_IN_GAIN, this);
    parameters.addParameterListener(Constants::ID_OUT_GAIN, this);
    parameters.addParameterListener(Constants::ID_ODD, this);
    parameters.addParameterListener(Constants::ID_EVEN, this);

    inGainRamper.initialize(*parameters.getRawParameterValue(Constants::ID_IN_GAIN), 0.01);
    outGainRamper.initialize(*parameters.getRawParameterValue(Constants::ID_OUT_GAIN), 0.01);
    oddRamper.initialize(*parameters.getRawParameterValue(Constants::ID_ODD), 0.01);
    evenRamper.initialize(*parameters.getRawParameterValue(Constants::ID_EVEN), 0.0001);
    
    //evenPower = dynamic_cast<AudioParameterInt*>(parameters.getParameter(Constants::EVEN_POWER));
    
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
        float oddPower = oddRamper.getNext();
        float evenPower = evenRamper.getNext();
        float outLevel = Decibels::decibelsToGain(outGainRamper.getNext());
        
        for (auto channel = 0 ; channel < buffer.getNumChannels() ; channel++)
        {
            //Get the current sample
            inSample = buffer.getSample(channel, sample);
            
            //Apply In Gain
            inSample *= inLevel;
            
            //Saturate the Sample
            outSample = CrispySaturator::saturateSample(inSample, oddPower, evenPower, true);
            
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
    if (parameterID == Constants::ID_IN_GAIN) {
        inGainRamper.updateTarget(newValue);
    } else if (parameterID == Constants::ID_OUT_GAIN) {
        outGainRamper.updateTarget(newValue);
    } else if (parameterID == Constants::ID_ODD) {
        oddRamper.updateTarget(newValue);
    } else if (parameterID == Constants::ID_EVEN) {
        evenRamper.updateTarget(newValue);
    }
}

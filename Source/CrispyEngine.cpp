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
    parameters.addParameterListener(Constants::IN_GAIN, this);
    parameters.addParameterListener(Constants::OUT_GAIN, this);
    parameters.addParameterListener(Constants::ODD_POWER, this);
    parameters.addParameterListener(Constants::EVEN_POWER, this);
    parameters.addParameterListener(Constants::EVEN_MIX, this);

    inGainRamper.initialize(*parameters.getRawParameterValue(Constants::IN_GAIN), 0.1);
    outGainRamper.initialize(*parameters.getRawParameterValue(Constants::OUT_GAIN), 0.1);
    oddPowerRamper.initialize(*parameters.getRawParameterValue(Constants::ODD_POWER), 0.1);
    evenPowerRamper.initialize(*parameters.getRawParameterValue(Constants::EVEN_POWER), 0.1);
    evenMixRamper.initialize(*parameters.getRawParameterValue(Constants::EVEN_MIX), 0.1);
    
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
        float oddPower = oddPowerRamper.getNext();
        float evenPower = evenPowerRamper.getNext();
        float evenMix = evenMixRamper.getNext();
        float outLevel = Decibels::decibelsToGain(outGainRamper.getNext());
        
        for (auto channel = 0 ; channel < buffer.getNumChannels() ; channel++)
        {
            //Get the current sample
            inSample = buffer.getSample(channel, sample);
            
            //Apply In Gain
            inSample *= inLevel;
            
            //Saturate the Sample
            outSample = CrispySaturator::saturateSample(inSample, oddPower, evenPower, evenMix);
            
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
    if (parameterID == Constants::IN_GAIN) {
        inGainRamper.updateTarget(newValue);
    } else if (parameterID == Constants::OUT_GAIN) {
        outGainRamper.updateTarget(newValue);
    } else if (parameterID == Constants::ODD_POWER) {
        oddPowerRamper.updateTarget(newValue);
    } else if (parameterID == Constants::EVEN_POWER) {
        evenPowerRamper.updateTarget(newValue);
    } else if (parameterID == Constants::EVEN_MIX) {
        evenMixRamper.updateTarget(newValue);
    }
    
    DebugWindow::debugLines[2] = String(oddPowerRamper.getNext());
    DebugWindow::debugLines[3] = String(evenPowerRamper.getNext());
    DebugWindow::debugLines[4] = String(evenMixRamper.getNext());
}

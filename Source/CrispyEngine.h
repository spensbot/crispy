/*
  ==============================================================================

    CrispyEngine.h
    Created: 13 Dec 2019 2:24:38pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "RamperLinear.h"
#include "CrispySaturator.h"
#include "RecirculatingBuffer.h"

class CrispyEngine: public AudioProcessorValueTreeState::Listener
{
public:
    CrispyEngine(AudioProcessorValueTreeState&);
    
    void process(AudioBuffer<float>& buffer);
    
    void parameterChanged(const String& parameterID, float newValue ) override;
    
    RecirculatingBuffer inBuffer, outBuffer;
    
private:
    AudioProcessorValueTreeState& parameters;
    
    RamperLinear inGainRamper, outGainRamper, saturationRamper;
    
};

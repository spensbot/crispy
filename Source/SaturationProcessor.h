/*
  ==============================================================================

    SaturationProcessor.h
    Created: 3 Apr 2020 5:46:45pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"

class SaturationProcessor : dsp::ProcessorBase
{
public:
    void prepare (const dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;
        
        float lowPassFreq = *parameters.getRawParameterValue(Constants::ID_LOW_PASS_FREQ);
        setLowPassFreq(lowPassFreq);
        
        float hiPassFreq = *parameters.getRawParameterValue(Constants::ID_HI_PASS_FREQ);
        setHiPassFreq(hiPassFreq);
        
        processorChain.prepare(spec);
    }
    
    void process (const dsp::ProcessContextReplacing<float>& context) override
    {
        processorChain.process(context);
    }
    
    void reset () override
    {
        processorChain.reset();
    }
    
private:
    
    
    
}

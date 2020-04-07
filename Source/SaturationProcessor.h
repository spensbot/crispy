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

class SaturationProcessor : public AudioProcessorValueTreeState::Listener, public dsp::ProcessorBase
{
public:
    SaturationProcessor(AudioProcessorValueTreeState& params) : parameters(params)
    {
        parameters.addParameterListener(Constants::ID_EVEN, this);
        parameters.addParameterListener(Constants::ID_ODD, this);
        parameters.addParameterListener(Constants::ID_AUTO_GAIN_AMOUNT, this);
    }
    
    void prepare (const dsp::ProcessSpec& spec) override
    {
        dcFilter.prepare(spec);
        autoGain.prepare(spec);
    }
    
    void process (const dsp::ProcessContextReplacing<float>& context) override
    {
        autoGain.process(context);
        
        saturatorOdd.process(context);
        saturatorEven.process(context);
        dcFilter.process(context);
        
        //autoGain.processRemoveGain(context);
    }
    
    void reset () override
    {
        dcFilter.reset();
        autoGain.reset();
    }
    
    void parameterChanged (const String& parameterID, float newValue) override
    {
        if (parameterID == Constants::ID_EVEN)
        {
            saturatorEven.setAmount(newValue);
        }
        else if (parameterID == Constants::ID_ODD)
        {
            saturatorOdd.setAmount(newValue);
        }
        else if (parameterID == Constants::ID_AUTO_GAIN_AMOUNT)
        {
            autoGain.setAmount(newValue);
        }
    }
    
private:
    
    AudioProcessorValueTreeState& parameters;
    
    stm::SaturatorCrispyOdd saturatorOdd;
    stm::SaturatorCrispyEven saturatorEven;
    stm::DCFilter dcFilter;
    stm::AutoGain autoGain;
    
};

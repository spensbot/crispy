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
    SaturationProcessor(AudioProcessorValueTreeState& params)
    : parameters(params)
    , oversamplingEngine(2, 3, dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR)
    {
        parameters.addParameterListener(Constants::ID_SATURATION, this);
        parameters.addParameterListener(Constants::ID_ODD_EVEN_MIX, this);
        parameters.addParameterListener(Constants::ID_AUTO_GAIN_AMOUNT, this);
        parameters.addParameterListener(Constants::ID_OVERSAMPLING, this);
        
        oddEvenMix = parameters.getRawParameterValue(Constants::ID_ODD_EVEN_MIX);
        saturation = parameters.getRawParameterValue(Constants::ID_SATURATION);
    }
    
    void prepare (const dsp::ProcessSpec& spec) override
    {
        dcFilter.prepare(spec);
        autoGain.prepare(spec);
        oversamplingEngine.initProcessing(spec.maximumBlockSize);
    }
    
    void process (const dsp::ProcessContextReplacing<float>& context) override
    {
        autoGain.process(context);
        
        saturator.process(context);
        dcFilter.process(context);
        
        autoGain.processRemoveGain(context);
    }
    
    void reset () override
    {
        dcFilter.reset();
        autoGain.reset();
        oversamplingEngine.reset();
    }
    
    void parameterChanged (const String& parameterID, float newValue) override
    {
        if (parameterID == Constants::ID_SATURATION || parameterID == Constants::ID_ODD_EVEN_MIX)
        {
            saturator.set(*oddEvenMix, *saturation);
        }
        else if (parameterID == Constants::ID_AUTO_GAIN_AMOUNT)
        {
            autoGain.setAmount(newValue);
        }
        else if (parameterID == Constants::ID_OVERSAMPLING)
        {
            autoGain.setAmount(newValue);
        }
    }
    
private:
    
    AudioProcessorValueTreeState& parameters;
    
    dsp::Oversampling<float> oversamplingEngine;
    
    std::atomic<float>* oddEvenMix;
    std::atomic<float>* saturation;
    
    stm::SaturatorCrispy saturator;
    
    stm::DCFilter dcFilter;
    stm::AutoGain autoGain;
    
};

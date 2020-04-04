/*
  ==============================================================================

    InputFilter.h
    Created: 3 Apr 2020 8:49:43am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"

class InputFilter : public dsp::ProcessorBase, public AudioProcessorValueTreeState::Listener {
public:
    
    InputFilter(AudioProcessorValueTreeState& params) : parameters(params)
    {
        parameters.addParameterListener(Constants::ID_LOW_PASS_FREQ, this);
        parameters.addParameterListener(Constants::ID_HI_PASS_FREQ, this);
    }
    
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
    
    void parameterChanged (const String& parameterID, float newValue) override
    {
        if (parameterID == Constants::ID_LOW_PASS_FREQ)
        {
            setLowPassFreq(newValue);
        }
        else if (parameterID == Constants::ID_HI_PASS_FREQ)
        {
            setHiPassFreq(newValue);
        }
    }
    
private:
    const float Q = 24.0f; // filter db/octave
    
    double sampleRate = 44000.0;
    
    enum {
        hiPassIndex,
        lowPassIndex
    };
    
    AudioProcessorValueTreeState& parameters;
    
    using Filter = dsp::IIR::Filter<float>;
    using FilterCoefs = dsp::IIR::Coefficients<float>;
    using DuplicatedFilter = dsp::ProcessorDuplicator<Filter, FilterCoefs>;

    dsp::ProcessorChain<DuplicatedFilter, DuplicatedFilter> processorChain;
    
    void setLowPassFreq(float newFreq){
        auto lowPassCoefs = FilterCoefs::makeLowPass(sampleRate, newFreq, Q);
        
        auto& lowPassFilter = processorChain.get<lowPassIndex>();
        
        *(lowPassFilter.state) = *lowPassCoefs;
        
        lowPassFilter.reset();
    }
    
    void setHiPassFreq(float newFreq){
        auto hiPassCoefs = FilterCoefs::makeHighPass(sampleRate, newFreq, Q);
        
        auto& hiPassFilter = processorChain.template get<hiPassIndex>();
        
        *(hiPassFilter.state) = *hiPassCoefs;
        
        hiPassFilter.reset();
    }
};



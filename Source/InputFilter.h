/*
  ==============================================================================

    InputFilter.h
    Created: 3 Apr 2020 8:49:43am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Params.h"

class InputFilter : public dsp::ProcessorBase, public AudioProcessorValueTreeState::Listener {
public:
    
    InputFilter(AudioProcessorValueTreeState& params) : parameters(params)
    {
        parameters.addParameterListener(Params::ID_LOW_PASS_FREQ, this);
        parameters.addParameterListener(Params::ID_HI_PASS_FREQ, this);
    }
    
    void prepare (const dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;
        
        float lowPassFreq = *parameters.getRawParameterValue(Params::ID_LOW_PASS_FREQ);
        setLowPassFreq(lowPassFreq);
        
        float hiPassFreq = *parameters.getRawParameterValue(Params::ID_HI_PASS_FREQ);
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
        if (parameterID == Params::ID_LOW_PASS_FREQ)
        {
            setLowPassFreq(newValue);
        }
        else if (parameterID == Params::ID_HI_PASS_FREQ)
        {
            setHiPassFreq(newValue);
        }
    }
    
private:
    const float Q = 1.0f;
    
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
        //auto lowPassCoefs = FilterCoefs::makeFirstOrderLowPass(sampleRate, newFreq);
        
        auto& lowPassFilter = processorChain.get<lowPassIndex>();
        
        *(lowPassFilter.state) = *lowPassCoefs;
        
        lowPassFilter.reset();
    }
    
    void setHiPassFreq(float newFreq){
        auto hiPassCoefs = FilterCoefs::makeHighPass(sampleRate, newFreq, Q);
        //auto hiPassCoefs = FilterCoefs::makeFirstOrderHighPass(sampleRate, newFreq);
        
        auto& hiPassFilter = processorChain.template get<hiPassIndex>();
        
        *(hiPassFilter.state) = *hiPassCoefs;
        
        hiPassFilter.reset();
    }
};

// -------------------------------------------------------------------------------------------------
// ****************************    VARIABLE VERSION OF THE FILTER ABOVE    *************************
// -------------------------------------------------------------------------------------------------

class InputFilterVariable : public dsp::ProcessorBase, public AudioProcessorValueTreeState::Listener {
public:
    
    InputFilterVariable(AudioProcessorValueTreeState& params) : parameters(params)
    {
        parameters.addParameterListener(Params::ID_LOW_PASS_FREQ, this);
        parameters.addParameterListener(Params::ID_HI_PASS_FREQ, this);
    }
    
    void prepare (const dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;
        
        auto& lowPassFilter = processorChain.get<lowPassIndex>();
        lowPassFilter.setType(dsp::StateVariableTPTFilterType::lowpass);
        lowPassFilter.setResonance(1 / sqrt(2));
        float lowPassFreq = *parameters.getRawParameterValue(Params::ID_LOW_PASS_FREQ);
        lowPassFilter.setCutoffFrequency(lowPassFreq);
        
        auto& hiPassFilter = processorChain.get<hiPassIndex>();
        hiPassFilter.setType(dsp::StateVariableTPTFilterType::highpass);
        hiPassFilter.setResonance(1 / sqrt(2));
        float hiPassFreq = *parameters.getRawParameterValue(Params::ID_HI_PASS_FREQ);
        hiPassFilter.setCutoffFrequency(hiPassFreq);
        
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
        if (parameterID == Params::ID_LOW_PASS_FREQ)
        {
            setLowPassFreq(newValue);
        }
        else if (parameterID == Params::ID_HI_PASS_FREQ)
        {
            setHiPassFreq(newValue);
        }
    }
    
private:
    const float Q = 1.0f;
    
    double sampleRate = 44000.0;
    
    enum {
        hiPassIndex,
        lowPassIndex
    };
    
    AudioProcessorValueTreeState& parameters;
    
    using Filter = dsp::StateVariableTPTFilter<float>;
    dsp::ProcessorChain<Filter, Filter> processorChain;
    
    void setLowPassFreq(float newFreq){
        auto& lowPassFilter = processorChain.get<lowPassIndex>();
        lowPassFilter.setCutoffFrequency(newFreq);
    }
    
    void setHiPassFreq(float newFreq){
        auto& hiPassFilter = processorChain.template get<hiPassIndex>();
        hiPassFilter.setCutoffFrequency(newFreq);
    }
};



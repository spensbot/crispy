/*
  ==============================================================================

    CrispyEngine.h
    Created: 13 Dec 2019 2:24:38pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"
#include "InputFilter.h"
#include "SaturationProcessor.h"

class CrispyEngine: public dsp::ProcessorBase, public AudioProcessorValueTreeState::Listener
{
public:
    
    CrispyEngine(AudioProcessorValueTreeState& params)
    : parameters(params)
    , inputFilter(params)
    , saturation(params)
    {
        parameters.addParameterListener(Constants::ID_IN_GAIN, this);
        parameters.addParameterListener(Constants::ID_BYPASS, this);
        parameters.addParameterListener(Constants::ID_DRY_GAIN, this);
        parameters.addParameterListener(Constants::ID_WET_GAIN, this);

        inGain.setGainDecibels(*parameters.getRawParameterValue(Constants::ID_IN_GAIN));
        
        
        const int bufferSize = 100000;
        
        inBuffer.prepare(bufferSize);
        outBuffer.prepare(bufferSize);
    }
    
    void prepare(const dsp::ProcessSpec& spec) override
    {
        dryBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
        inGain.prepare(spec);
        inputFilter.prepare(spec);
        saturation.prepare(spec);
        dryWetMix.prepare(spec);
        matchedBypass.prepare(spec);
    }
    
    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        auto inBlock = context.getInputBlock();
        
        size_t numSamples = inBlock.getNumSamples();
        auto dryBlock = dsp::AudioBlock<float>(dryBuffer).getSubBlock(0, numSamples);
        dryBlock.copyFrom(inBlock);
        
        inGain.process(context);
        inputFilter.process(context);
        saturation.process(context);
        dryWetMix.process(context, dryBlock);
        matchedBypass.process(context, dryBlock);
    }
    
    void reset() override
    {
        inGain.reset();
        inputFilter.reset();
        saturation.reset();
        dryWetMix.reset();
        matchedBypass.reset();
    }
    
    void parameterChanged(const String& parameterID, float newValue ) override {
        
        if (parameterID == Constants::ID_IN_GAIN) {
            inGain.setGainDecibels(newValue);
        }
        else if (parameterID == Constants::ID_DRY_GAIN) {
            dryWetMix.setDryDecibels(newValue);
        }
        else if (parameterID == Constants::ID_WET_GAIN) {
            dryWetMix.setWetDecibels(newValue);
        }
        else if (parameterID == Constants::ID_BYPASS) {
            stm::DebugDisplay::add(5, "Bypass Value: " + String(newValue));
            
            if (newValue > 0.5) {
                matchedBypass.setActive(true);
            } else {
                matchedBypass.setActive(false);
            }
        }
    }
    
    stm::RecircBuffer inBuffer, outBuffer;
    
private:
    AudioProcessorValueTreeState& parameters;
    
    AudioSampleBuffer dryBuffer;
    
    dsp::Gain<float> inGain;
    
    InputFilter inputFilter;
    SaturationProcessor saturation;
    stm::DryWetMix dryWetMix;
    stm::MatchedBypass matchedBypass;
};

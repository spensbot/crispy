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

class CrispyEngine: public dsp::ProcessorBase, public AudioProcessorValueTreeState::Listener
{
public:
    CrispyEngine(AudioProcessorValueTreeState& params) : parameters(params), inputFilter(params)
    {
        parameters.addParameterListener(Constants::ID_IN_GAIN, this);
        parameters.addParameterListener(Constants::ID_LOW_PASS_FREQ, this);
        parameters.addParameterListener(Constants::ID_HI_PASS_FREQ, this);
        parameters.addParameterListener(Constants::ID_NORMALIZE_ATTACK, this);
        parameters.addParameterListener(Constants::ID_NORMALIZE_RELEASE, this);
        parameters.addParameterListener(Constants::ID_NORMALIZE_AMOUNT, this);
        parameters.addParameterListener(Constants::ID_ODD, this);
        parameters.addParameterListener(Constants::ID_EVEN, this);
        parameters.addParameterListener(Constants::ID_WET_DRY, this);
        parameters.addParameterListener(Constants::ID_OUT_GAIN, this);

        lowPassFreqRamper.initialize(*parameters.getRawParameterValue(Constants::ID_LOW_PASS_FREQ), 0.1);
        hiPassFreqRamper.initialize(*parameters.getRawParameterValue(Constants::ID_HI_PASS_FREQ), 0.1);
        normalizeAttackRamper.initialize(*parameters.getRawParameterValue(Constants::ID_NORMALIZE_ATTACK), 0.1);
        normalizeReleaseRamper.initialize(*parameters.getRawParameterValue(Constants::ID_NORMALIZE_RELEASE), 0.1);
        normalizeAmountRamper.initialize(*parameters.getRawParameterValue(Constants::ID_NORMALIZE_AMOUNT), 0.01);
        oddRamper.initialize(*parameters.getRawParameterValue(Constants::ID_ODD), 0.01);
        evenRamper.initialize(*parameters.getRawParameterValue(Constants::ID_EVEN), 0.0001);
        wetDryRamper.initialize(*parameters.getRawParameterValue(Constants::ID_WET_DRY), 0.01);
        outGainRamper.initialize(*parameters.getRawParameterValue(Constants::ID_OUT_GAIN), 0.01);
        
        inGain.setGainDecibels(*parameters.getRawParameterValue(Constants::ID_IN_GAIN));
        
        const int bufferSize = 100000;
        
        inBuffer.reset(bufferSize);
        outBuffer.reset(bufferSize);
    }
    
    void prepare(const dsp::ProcessSpec& spec) override
    {
        inGain.prepare(spec);
        inputFilter.prepare(spec);
    }
    
    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        inGain.process(context);
        inputFilter.process(context);
    }
    
    void reset() override
    {
        inGain.reset();
        inputFilter.reset();
    }
    
    void parameterChanged(const String& parameterID, float newValue ) override {
        stm::DebugDisplay::debugLines[5] = parameterID + " changed to: " + String(newValue);
        
        if (parameterID == Constants::ID_IN_GAIN) {
            inGain.setGainDecibels(newValue);
        }
        else if (parameterID == Constants::ID_LOW_PASS_FREQ) {
            lowPassFreqRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_HI_PASS_FREQ) {
            hiPassFreqRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_NORMALIZE_ATTACK) {
            normalizeAttackRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_NORMALIZE_RELEASE) {
            normalizeReleaseRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_NORMALIZE_AMOUNT) {
            normalizeAmountRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_ODD) {
            oddRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_EVEN) {
            evenRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_WET_DRY) {
            wetDryRamper.updateTarget(newValue);
        }
        else if (parameterID == Constants::ID_OUT_GAIN) {
            outGainRamper.updateTarget(newValue);
        }
    }
    
    stm::RecircBuffer inBuffer, outBuffer;
    
private:
    AudioProcessorValueTreeState& parameters;
    
    dsp::Gain<float> inGain;
    InputFilter inputFilter;
    
    //std::vector<ProcessorBase> processors;
    
    stm::RamperLinear lowPassFreqRamper
        , hiPassFreqRamper
        , normalizeAttackRamper
        , normalizeReleaseRamper
        , normalizeAmountRamper
        , oddRamper
        , evenRamper
        , wetDryRamper
        , outGainRamper;
    
};

/*
  ==============================================================================

    CrispyEngine.h
    Created: 13 Dec 2019 2:24:38pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Params.h"
#include "InputFilter.h"
#include "SaturationProcessor.h"

class CrispyEngine: public dsp::ProcessorBase, public AudioProcessorValueTreeState::Listener
{
public:
    CrispyEngine(AudioProcessorValueTreeState& params, AudioProcessor& p);
    
    void prepare(const dsp::ProcessSpec& spec) override;
    
    void process(const dsp::ProcessContextReplacing<float>& context) override;
    
    void reset() override;
    
    void parameterChanged(const String& parameterID, float newValue ) override;
    
    void setLatencySamples(float newLatency);
    
    stm::RecircBuffer inBuffer, outBuffer;
    
private:
    AudioProcessorValueTreeState& parameters;
    AudioProcessor& processor;
    
    AudioSampleBuffer dryBuffer;
    
    std::atomic<float>* isMoreControl;
    
    //InputFilter inputFilter;
    InputFilterVariable inputFilter;
    SaturationProcessor saturation;
    stm::DryWetMix dryWetMix;
    stm::MatchedBypass matchedBypass;
    stm::DelaySimple latencyDelay;
    
    void updateParameters();
};

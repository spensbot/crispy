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

class CrispyEngine;

class SaturationProcessor : public AudioProcessorValueTreeState::Listener, public dsp::ProcessorBase
{
public:
    SaturationProcessor(AudioProcessorValueTreeState& params, CrispyEngine& engine);
    
    void prepare (const dsp::ProcessSpec& _spec) override;
    
    void process (const dsp::ProcessContextReplacing<float>& context) override;
    
    void reset () override;
    
    void parameterChanged (const String& parameterID, float newValue) override;
    
private:
    dsp::ProcessSpec spec;
    
    AudioProcessorValueTreeState& parameters;
    CrispyEngine& crispyEngine;
    
    dsp::Oversampling<float>* oversamplingEngine;
    
    OwnedArray<dsp::Oversampling<float>, CriticalSection> oversamplingEngines;
    
    std::atomic<float>* oddEvenMix;
    std::atomic<float>* saturation;
    std::atomic<float>* isMoreControl;
    
    stm::SaturatorCrispy saturator;
    stm::DCFilter dcFilter;
    stm::AutoGain autoGain;
                                           
    void setOversamplingEngine(int index);
};

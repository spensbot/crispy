/*
  ==============================================================================

    SaturationProcessor.cpp
    Created: 13 Apr 2020 6:48:36pm
    Author:  Spenser Saling

  ==============================================================================
*/

#include "SaturationProcessor.h"
#include "CrispyEngine.h"

SaturationProcessor::SaturationProcessor(AudioProcessorValueTreeState& params, CrispyEngine& engine)
: parameters(params)
, crispyEngine(engine)
{
    parameters.addParameterListener(Constants::ID_SATURATION, this);
    parameters.addParameterListener(Constants::ID_ODD_EVEN_MIX, this);
    parameters.addParameterListener(Constants::ID_AUTO_GAIN_AMOUNT, this);
    parameters.addParameterListener(Constants::ID_OVERSAMPLING, this);
    
    oddEvenMix = parameters.getRawParameterValue(Constants::ID_ODD_EVEN_MIX);
    saturation = parameters.getRawParameterValue(Constants::ID_SATURATION);
    isMoreControl = parameters.getRawParameterValue(Constants::ID_MORE_CONTROL);
}

void SaturationProcessor::prepare (const dsp::ProcessSpec& _spec)
{
    spec = _spec;
    
    //Prepare processors that don't deal with oversampled audio
    autoGain.prepare(spec);
    dcFilter.prepare(spec);
    
    //Prepare the oversampling engines
    for (auto i=0 ; i<5; ++i){
        oversamplingEngines.add(new dsp::Oversampling<float>(2, i, dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR));
        oversamplingEngines[i]->initProcessing( spec.maximumBlockSize );
    }
    
    updateParameters();
}

void SaturationProcessor::process (const dsp::ProcessContextReplacing<float>& context)
{
    autoGain.process(context);
    auto& inBlock = context.getInputBlock();
    auto& outBlock = context.getOutputBlock();
    auto oversampledBlock = oversamplingEngine->processSamplesUp(inBlock);
    auto oversampledContext = dsp::ProcessContextReplacing<float> (oversampledBlock);
    stm::DebugDisplay::set(19, "Regular: " + String(inBlock.getNumSamples()));
    stm::DebugDisplay::set(20, "Oversampled: " + String(oversampledBlock.getNumSamples()));
    saturator.process(oversampledContext);
    oversamplingEngine->processSamplesDown(outBlock);
    dcFilter.process(context);
    autoGain.processRemoveGain(context);
}

void SaturationProcessor::reset ()
{
    saturator.reset();
    dcFilter.reset();
    autoGain.reset();
}

void SaturationProcessor::parameterChanged (const String& parameterID, float newValue)
{
    if (parameterID == Constants::ID_SATURATION)
    {
        saturator.setOdd(newValue);
    }
    else if (parameterID == Constants::ID_ODD_EVEN_MIX)
    {
        saturator.setEven(newValue);
    }
    else if (parameterID == Constants::ID_AUTO_GAIN_AMOUNT)
    {
        autoGain.setAmount(newValue);
    }
    else if (parameterID == Constants::ID_OVERSAMPLING)
    {
        setOversamplingEngine( int(newValue) );
    }
}
                                       
void SaturationProcessor::setOversamplingEngine(int index){
    //Change the oversampling engine
    oversamplingEngine = oversamplingEngines[index];
    
    //Create a ProcessSpec for the oversampled processes
    auto oversamplingMultiplier = oversamplingEngine->getOversamplingFactor();
    auto oversamplingSampleRate = spec.sampleRate * oversamplingMultiplier;
    auto oversamplingBlockSize = spec.maximumBlockSize * oversamplingMultiplier;
    dsp::ProcessSpec oversamplingSpec = {oversamplingSampleRate, (uint32) oversamplingBlockSize, spec.numChannels};
    
    //Prepare the oversampled processes
    saturator.prepare(oversamplingSpec);
    
    //Tell crispy engine to notify the daw and compensate for latency
    crispyEngine.setLatencySamples(oversamplingEngine->getLatencyInSamples());
    
    stm::DebugDisplay::set(10, "Oversampling Latency: " + String(oversamplingEngine->getLatencyInSamples()) + "samples");
    stm::DebugDisplay::set(11, "Oversampling Multiplier: " + String(oversamplingMultiplier));
    stm::DebugDisplay::set(12, "Oversampling Sample Rate: " + String(oversamplingSpec.sampleRate));
    stm::DebugDisplay::set(13, "Oversampling Block Size: " + String(oversamplingSpec.maximumBlockSize));
}

void SaturationProcessor::updateParameters()
{
    saturator.setOdd(*parameters.getRawParameterValue(Constants::ID_SATURATION));
    saturator.setEven(*parameters.getRawParameterValue(Constants::ID_ODD_EVEN_MIX));
    autoGain.setAmount(*parameters.getRawParameterValue(Constants::ID_AUTO_GAIN_AMOUNT));
    setOversamplingEngine( int( *parameters.getRawParameterValue(Constants::ID_OVERSAMPLING) ) );
}

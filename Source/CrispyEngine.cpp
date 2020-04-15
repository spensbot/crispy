/*
  ==============================================================================

    CrispyEngine.cpp
    Created: 13 Apr 2020 6:36:17pm
    Author:  Spenser Saling

  ==============================================================================
*/

#include "CrispyEngine.h"
#include "SaturationProcessor.h"
    
CrispyEngine::CrispyEngine(AudioProcessorValueTreeState& params, AudioProcessor& p)
: parameters(params)
, processor(p)
, inputFilter(params)
, saturation(params, *this)
{
    parameters.addParameterListener(Constants::ID_BYPASS, this);
    parameters.addParameterListener(Constants::ID_DRY_GAIN, this);
    parameters.addParameterListener(Constants::ID_WET_GAIN, this);
    
    const int bufferSize = 100000;
    
    inBuffer.prepare(bufferSize);
    outBuffer.prepare(bufferSize);
    
    isMoreControl = parameters.getRawParameterValue(Constants::ID_MORE_CONTROL);
    
    latencyDelay.setBufferSamples(1000);
}

void CrispyEngine::prepare(const dsp::ProcessSpec& spec)
{
    dryBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
    inputFilter.prepare(spec);
    saturation.prepare(spec);
    dryWetMix.prepare(spec);
    matchedBypass.prepare(spec);
    latencyDelay.prepare(spec);
    
    updateParameters();
}

void CrispyEngine::process(const dsp::ProcessContextReplacing<float>& context)
{
    // Create a copy of the input block to use as the dry signal.
    auto inBlock = context.getInputBlock();
    size_t numSamples = inBlock.getNumSamples();
    auto dryBlock = dsp::AudioBlock<float>(dryBuffer).getSubBlock(0, numSamples);
    dryBlock.copyFrom(inBlock);
    // Create a context from the dry block for use in latencyDelay
    auto dryContext = dsp::ProcessContextReplacing<float> (dryBlock);
    
    latencyDelay.process(dryContext);
    
    inputFilter.process(context);
    saturation.process(context);
    dryWetMix.process(context, dryBlock);
    matchedBypass.process(context, dryBlock);
}

void CrispyEngine::reset()
{
    inputFilter.reset();
    saturation.reset();
    dryWetMix.reset();
    matchedBypass.reset();
}

void CrispyEngine::parameterChanged(const String& parameterID, float newValue )
{
    if (parameterID == Constants::ID_DRY_GAIN) {
        dryWetMix.setDryDecibels(newValue);
    }
    else if (parameterID == Constants::ID_WET_GAIN) {
        dryWetMix.setWetDecibels(newValue);
    }
    else if (parameterID == Constants::ID_BYPASS) {
        if (newValue > 0.5) {
            matchedBypass.setActive(true);
        } else {
            matchedBypass.setActive(false);
        }
    }
}

void CrispyEngine::setLatencySamples(float newLatency)
{
    int newLatencyInt = roundToInt(newLatency);
    processor.setLatencySamples(newLatencyInt);
    latencyDelay.setDelaySamples(newLatencyInt);
    stm::DebugDisplay::set(15, "Dry Latency Samples Set: " + String(newLatencyInt));
}

void CrispyEngine::updateParameters()
{
    dryWetMix.setDryDecibels(*parameters.getRawParameterValue(Constants::ID_DRY_GAIN));
    dryWetMix.setWetDecibels(*parameters.getRawParameterValue(Constants::ID_WET_GAIN));
    matchedBypass.setActive(*parameters.getRawParameterValue(Constants::ID_BYPASS));
}


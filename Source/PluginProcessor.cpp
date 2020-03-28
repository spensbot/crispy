/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CrispySaturatorAudioProcessor::CrispySaturatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
parameters (*this, &undoManager, Identifier ("APVTSTutorial"),
{
    std::make_unique<AudioParameterFloat> ("inGain", "In Gain", -18.0f, 18.0f, 0.0f),
    std::make_unique<AudioParameterFloat> ("outGain", "Out Gain", -18.0f, 18.0f, 0.0f),
    std::make_unique<AudioParameterFloat> ("saturation", "Saturation", NormalisableRange<float>(0.01f, 100.0f, 0.01f,
                                                                                                std::log (0.5f) / std::log ((1.0 - 0.01) / (100.0 - 0.01))), 1.0f),
})
, crispyEngine(parameters)
{
    
}

CrispySaturatorAudioProcessor::~CrispySaturatorAudioProcessor()
{
}

//==============================================================================
const String CrispySaturatorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CrispySaturatorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CrispySaturatorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CrispySaturatorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CrispySaturatorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CrispySaturatorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CrispySaturatorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CrispySaturatorAudioProcessor::setCurrentProgram (int index)
{
}

const String CrispySaturatorAudioProcessor::getProgramName (int index)
{
    return {};
}

void CrispySaturatorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CrispySaturatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void CrispySaturatorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CrispySaturatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CrispySaturatorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    crispyEngine.process(buffer);
}

//==============================================================================
bool CrispySaturatorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CrispySaturatorAudioProcessor::createEditor()
{
    return new CrispySaturatorAudioProcessorEditor (*this);
}

//==============================================================================
void CrispySaturatorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CrispySaturatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CrispySaturatorAudioProcessor();
}

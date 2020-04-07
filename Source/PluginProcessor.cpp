/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

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
    std::make_unique<AudioParameterFloat> (Constants::ID_IN_GAIN, "In Gain", 0.0f, 24.0f, 0.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_LOW_PASS_FREQ,
                                           "Low Pass Frequency",
                                           NormalisableRange<float>(20.0f, 20000.0f, 0.1f, 0.3f),
                                           20000.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_HI_PASS_FREQ,
                                           "High Pass Frequency",
                                           NormalisableRange<float>(20.0f, 20000.0f, 0.1f, 0.3f),
                                           20.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_AUTO_GAIN_AMOUNT, "Auto Gain Amount", 0.0f, 1.0f, 0.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_OVERSAMPLING,
                                           "Oversampling",
                                           NormalisableRange<float>(0.0f, 8.0f, 2.0f),
                                           0.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_ODD,
                                           "Odd Harmonics",
                                           NormalisableRange<float>(1.0f, 100.0f, 0.01f, 0.3f),
                                           1.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_EVEN, "Even Harmonics", 0.0f, 1.0f, 0.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_WET_GAIN,
                                           "Wet Gain",
                                           NormalisableRange<float>(-100.0f, 6.0f, 0.01f, 3.0f),
                                           0.0f),
    
    std::make_unique<AudioParameterFloat> (Constants::ID_DRY_GAIN,
                                           "Dry Gain",
                                           NormalisableRange<float>(-100.0f, 6.0f, 0.01f, 3.0f),
                                           0.0f),
    
    std::make_unique<AudioParameterBool> (Constants::ID_BYPASS, "Bypass", false)

    // equation for calculating skew factor for center point
    // std::log (0.5f) / std::log ((10.0 - 1.0) / (100.0 - 10.0))
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
    auto totalNumInputChannels  = getTotalNumInputChannels();
    
    crispyEngine.prepare({ sampleRate, (uint32) samplesPerBlock, (uint32) totalNumInputChannels });
    
    //Reports latency to the DAW
    setLatencySamples(0);
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
    // channels that didn't contain input data
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto block = juce::dsp::AudioBlock<float> (buffer);
    auto context = juce::dsp::ProcessContextReplacing<float> (block);
    crispyEngine.process(context);
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
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void CrispySaturatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
 
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CrispySaturatorAudioProcessor();
}

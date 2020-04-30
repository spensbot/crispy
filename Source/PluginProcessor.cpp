#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Params.h"

//==============================================================================
CrispySaturatorAudioProcessor::CrispySaturatorAudioProcessor() : 
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
parameters (*this, &undoManager, Identifier ("APVTSTutorial"), Params::createParameterLayout())
, crispyEngine(parameters, *this)
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

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CrispySaturatorAudioProcessorEditor::CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor& p)
: AudioProcessorEditor (&p)
,processor (p)
,parameters(p.parameters)
,saturationPanel(parameters)
,moreControlPanel(parameters)
{
    //setResizable(true, true);
    //setResizeLimits(300, 300, 1920, 1080);
    setSize (400, 630);
    
    setLookAndFeel(&crispyLookAndFeel);
    
    addAndMakeVisible(saturationPanel);
    addAndMakeVisible(moreControlPanel);
    
    addAndMakeVisible(debugDisplay);
    
    //addAndMakeVisible(bypassedVeil);
}

CrispySaturatorAudioProcessorEditor::~CrispySaturatorAudioProcessorEditor()
{
}

//==============================================================================
void CrispySaturatorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void CrispySaturatorAudioProcessorEditor::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    //debugDisplay.setBounds(bounds.removeFromLeft(getWidth() * 0.3));
    
    saturationPanel.setBounds(bounds.removeFromTop(getWidth()));
    moreControlPanel.setBounds(bounds);
    bypassedVeil.setBounds(getLocalBounds());
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

//==============================================================================
CrispySaturatorAudioProcessorEditor::CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
,parameters(p.parameters)
,inputWindow(parameters)
,harmonicsWindow(parameters)
,outputWindow(parameters)
,moreControlWindow(parameters)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(true, true);
    setResizeLimits(300, 300, 1920, 1080);
    setSize (600, 700);
    
    setLookAndFeel(&lookAndFeel);
    
    addAndMakeVisible(inputWindow);
    addAndMakeVisible(harmonicsWindow);
    addAndMakeVisible(outputWindow);
    addAndMakeVisible(moreControlWindow);
    
    addAndMakeVisible(debugDisplay);
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
    
    int inputWindowHeight = getHeight() / 6;
    int moreControlHeight = getHeight() / 4;
    
    if (processor.debug){
        debugDisplay.setBounds(bounds.removeFromLeft(getWidth() * 0.3));
    }
    
    inputWindow.setBounds(bounds.removeFromTop(inputWindowHeight));
    moreControlWindow.setBounds(bounds.removeFromBottom(moreControlHeight));
    outputWindow.setBounds(bounds.removeFromBottom(inputWindowHeight));
    harmonicsWindow.setBounds(bounds);
}

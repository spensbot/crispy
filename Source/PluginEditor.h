/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SaturationVisualizer.h"
#include "InputWindow.h"
#include "HarmonicsWindow.h"
#include "OutputWindow.h"
#include "MoreControlWindow.h"

//==============================================================================
/**
*/
class CrispySaturatorAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor&);
    ~CrispySaturatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    stm::StmLookAndFeel lookAndFeel;
    
    CrispySaturatorAudioProcessor& processor;
    AudioProcessorValueTreeState& parameters;
    
    InputWindow inputWindow;
    HarmonicsWindow harmonicsWindow;
    OutputWindow outputWindow;
    MoreControlWindow moreControlWindow;
    
    stm::DebugDisplay debugDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrispySaturatorAudioProcessorEditor)
};

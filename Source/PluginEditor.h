/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "BufferDrawer.h"
#include "SaturationVisualizer.h"
#include "LooknFeel.h"
#include "SaturationVisualizer2.h"
#include "SaturationWindow.h"
#include "DebugWindow.h"

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
    LooknFeel looknFeel;
    
    CrispySaturatorAudioProcessor& processor;
    AudioProcessorValueTreeState& parameters;
    
    Slider inGainSlider;
    Slider outGainSlider;
    
    std::unique_ptr<SliderAttachment> inGainSliderAttachment;
    std::unique_ptr<SliderAttachment> outGainSliderAttachment;
    
    BufferDrawer inBufferDrawer;
    BufferDrawer outBufferDrawer;
    SaturationWindow saturationWindow;
    
    DebugWindow debugWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrispySaturatorAudioProcessorEditor)
};

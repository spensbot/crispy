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
#include "CsLookAndFeel.h"
#include "SaturationVisualizer2.h"

//==============================================================================
/**
*/
class CrispySaturatorAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor&);
    ~CrispySaturatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider *slider) override;

private:
    CsLookAndFeel csLookAndFeel;
    
    CrispySaturatorAudioProcessor& processor;
    
    Slider inGainSlider;
    Slider outGainSlider;
    Slider saturationSlider;
    
    std::unique_ptr<SliderAttachment> inGainSliderAttachment;
    std::unique_ptr<SliderAttachment> outGainSliderAttachment;
    std::unique_ptr<SliderAttachment> saturationSliderAttachment;
    
    SaturationVisualizer saturationVisualizer;
    
    BufferDrawer inBufferDrawer;
    BufferDrawer outBufferDrawer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrispySaturatorAudioProcessorEditor)
};

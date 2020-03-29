/*
  ==============================================================================

    MoreControlWindow.h
    Created: 28 Mar 2020 8:45:31pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"
#include "DebugWindow.h"

//==============================================================================
/*
*/
class MoreControlWindow    : public Component
{
public:
    MoreControlWindow(AudioProcessorValueTreeState& params) : parameters(params)
    {
        initSlider(lowPassFreqSlider, lowPassFreqSliderAttachment, Constants::ID_LOW_PASS_FREQ);
        lowPassFreqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
        initSlider(hiPassFreqSlider, hiPassFreqSliderAttachment, Constants::ID_HI_PASS_FREQ);
        hiPassFreqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
        
        initSlider(normalizeAttackSlider, normalizeAttackSliderAttachment, Constants::ID_NORMALIZE_ATTACK);
        initSlider(normalizeReleaseSlider, normalizeReleaseSliderAttachment, Constants::ID_NORMALIZE_RELEASE);
        initSlider(normalizeAmountSlider, normalizeAmountSliderAttachment, Constants::ID_NORMALIZE_AMOUNT);
        
        initSlider(wetDrySlider, wetDrySliderAttachment, Constants::ID_WET_DRY);
    }

    ~MoreControlWindow()
    {
        
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colours::darkgrey);
        
    }

    void resized() override
    {
        int linearHeight = getHeight() * 0.1;
        int rotaryHeight = getHeight() * 0.15;
        
        Rectangle<int> bounds = getLocalBounds();
        
        lowPassFreqSlider.setBounds(bounds.removeFromTop(linearHeight));
        hiPassFreqSlider.setBounds(bounds.removeFromTop(linearHeight));
        
        normalizeAttackSlider.setBounds(bounds.removeFromTop(rotaryHeight));
        normalizeReleaseSlider.setBounds(bounds.removeFromTop(rotaryHeight));
        normalizeAmountSlider.setBounds(bounds.removeFromTop(rotaryHeight));
        
        wetDrySlider.setBounds(bounds.removeFromTop(rotaryHeight));
    }

private:
    AudioProcessorValueTreeState& parameters;
    
    Slider lowPassFreqSlider
        , hiPassFreqSlider
        , normalizeAttackSlider
        , normalizeReleaseSlider
        , normalizeAmountSlider
        , wetDrySlider;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    std::unique_ptr<SliderAttachment> lowPassFreqSliderAttachment
        , hiPassFreqSliderAttachment
        , normalizeAttackSliderAttachment
        , normalizeReleaseSliderAttachment
        , normalizeAmountSliderAttachment
        , wetDrySliderAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, String paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoreControlWindow)
};

//inline static const String ID_LOW_PASS_FREQ = "lowPassFreq";
//inline static const String ID_HI_PASS_FREQ = "hiPassFreq";
//inline static const String ID_NORMALIZE_ATTACK = "normalizeAttack";
//inline static const String ID_NORMALIZE_RELEASE = "normalizeRelease";
//inline static const String ID_NORMALIZE_AMOUNT = "normalizeAmount";
//inline static const String ID_WET_DRY = "wetDry";

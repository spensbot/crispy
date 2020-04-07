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

//==============================================================================
/*
*/
class MoreControlWindow    : public Component
{
public:
    MoreControlWindow(AudioProcessorValueTreeState& params) : parameters(params)
    {
        initSlider(autoGainAmountSlider, autoGainAmountSliderAttachment, Constants::ID_AUTO_GAIN_AMOUNT);
        initSlider(oversamplingSlider, oversamplingSliderAttachment, Constants::ID_OVERSAMPLING);
        initSlider(dryGainSlider, dryGainSliderAttachment, Constants::ID_DRY_GAIN);
        dryGainSlider.setSliderStyle(Slider::LinearVertical);
        initSlider(wetGainSlider, wetGainSliderAttachment, Constants::ID_WET_GAIN);
        wetGainSlider.setSliderStyle(Slider::LinearVertical);
        
        addAndMakeVisible(matchedBypassButton);
        matchedBypassButton.setButtonText("Matched Bypass");
        matchedBypassButton.setClickingTogglesState(true);
        matchedBypassButtonAttachment.reset(new ButtonAttachment(parameters, Constants::ID_BYPASS, matchedBypassButton));
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
        int padding = 5;
        int rotaryWidth = getWidth() / 4;
        int sliderWidth = 20;
        int bypassWidth = 80;
        int bypassHeight = 30;
        
        Rectangle<int> bounds = getLocalBounds();
        bounds.reduce(padding, padding);
        
        autoGainAmountSlider.setBounds(bounds.removeFromLeft(rotaryWidth));
        oversamplingSlider.setBounds(bounds.removeFromRight(rotaryWidth));
        
        int excess = bounds.getWidth() - 2*sliderWidth - 2*padding - bypassWidth;
        bounds.reduce(excess/2, 0);
        
        dryGainSlider.setBounds(bounds.removeFromLeft(sliderWidth));
        wetGainSlider.setBounds(bounds.removeFromRight(sliderWidth));
        bounds.reduce(padding, padding);
        matchedBypassButton.setBounds(bounds.removeFromBottom(bypassHeight));
    }

private:
    AudioProcessorValueTreeState& parameters;
    
    Slider autoGainAmountSlider,
        oversamplingSlider,
        dryGainSlider,
        wetGainSlider;
    
    TextButton matchedBypassButton;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
    std::unique_ptr<SliderAttachment> autoGainAmountSliderAttachment,
        oversamplingSliderAttachment,
        dryGainSliderAttachment,
        wetGainSliderAttachment;
    
    std::unique_ptr<ButtonAttachment> matchedBypassButtonAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, String paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        slider.setPopupDisplayEnabled(true, true, this);
        slider.setPopupMenuEnabled(true);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoreControlWindow)
};

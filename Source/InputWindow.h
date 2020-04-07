/*
  ==============================================================================

    InputWindow.h
    Created: 6 Apr 2020 12:08:09am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"

//==============================================================================
/*
*/
class InputWindow    : public Component
{
public:
    InputWindow(AudioProcessorValueTreeState& params) : parameters(params)
    {
        initSlider(lowPassFreqSlider, lowPassFreqSliderAttachment, Constants::ID_LOW_PASS_FREQ);
        initSlider(hiPassFreqSlider, hiPassFreqSliderAttachment, Constants::ID_HI_PASS_FREQ);
    }

    ~InputWindow()
    {
    }

    void paint (Graphics& g) override
    {
        
    }

    void resized() override
    {
        Rectangle<int> bounds = getLocalBounds();
        
        lowPassFreqSlider.setBounds(bounds.removeFromTop(getHeight()/2));
        hiPassFreqSlider.setBounds(bounds);
    }

private:
    AudioProcessorValueTreeState& parameters;
    
    Slider lowPassFreqSlider
        , hiPassFreqSlider;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    std::unique_ptr<SliderAttachment> lowPassFreqSliderAttachment
    , hiPassFreqSliderAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, const String& paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
        slider.setPopupDisplayEnabled(true, true, this);
        slider.setPopupMenuEnabled(true);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputWindow)
};

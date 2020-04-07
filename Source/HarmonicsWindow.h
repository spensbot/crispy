/*
  ==============================================================================

    HarmonicsWindow.h
    Created: 6 Apr 2020 12:09:32am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"

//==============================================================================
/*
*/
class HarmonicsWindow    : public Component, private Slider::Listener
{
public:
    HarmonicsWindow(AudioProcessorValueTreeState& params) : parameters(params)
    {
        addAndMakeVisible(saturationVisualizer);
        initSlider(oddSlider, oddSliderAttachment, Constants::ID_ODD);
        initSlider(evenSlider, evenSliderAttachment, Constants::ID_EVEN);
    }

    ~HarmonicsWindow()
    {
        
    }

    void paint (Graphics& g) override
    {
        
    }

    void resized() override
    {
        const int padding = getWidth()*0.03;
        Rectangle<int> bounds = getLocalBounds();
        saturationVisualizer.setBounds(bounds.removeFromTop(getHeight()/2));
        oddSlider.setBounds(bounds.removeFromLeft(getWidth()/2).reduced(padding));
        evenSlider.setBounds(bounds.reduced(padding * 3));
    }
    
    void sliderValueChanged (Slider *slider) override
    {
        saturationVisualizer.reset(oddSlider.getValue(), evenSlider.getValue());
        repaint();
    }

private:
    AudioProcessorValueTreeState& parameters;
    SaturationVisualizer saturationVisualizer;
    Slider oddSlider, evenSlider;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> oddSliderAttachment, evenSliderAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, String paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        slider.addListener(this);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonicsWindow)
};

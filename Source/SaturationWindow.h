/*
  ==============================================================================

    SaturationWindow.h
    Created: 28 Mar 2020 7:59:54am
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
class SaturationWindow    : public Component, private Slider::Listener
{
public:
    SaturationWindow(AudioProcessorValueTreeState& params)
    : parameters(params)
    {
        addAndMakeVisible(saturationVisualizer);
        initSlider(oddPowerSlider, oddPowerSliderAttachment, Constants::ODD_POWER);
        initSlider(evenPowerSlider, evenPowerSliderAttachment, Constants::EVEN_POWER);
        initSlider(evenMixSlider, evenMixSliderAttachment, Constants::EVEN_MIX);
    }

    ~SaturationWindow()
    {
        
    }

    void paint (Graphics& g) override
    {
        
    }

    void resized() override
    {
        Rectangle<int> bounds = getLocalBounds();
        saturationVisualizer.setBounds(bounds);
        oddPowerSlider.setBounds(bounds.removeFromLeft(getWidth()/2));
        evenPowerSlider.setBounds(bounds.removeFromTop(getHeight()/2));
        evenMixSlider.setBounds(bounds);
    }
    
    void sliderValueChanged (Slider *slider) override
    {
        
        saturationVisualizer.reset(oddPowerSlider.getValue(), evenPowerSlider.getValue(), evenMixSlider.getValue());
        repaint();
    }

private:
    AudioProcessorValueTreeState& parameters;
    SaturationVisualizer2 saturationVisualizer;
    Slider oddPowerSlider, evenPowerSlider, evenMixSlider;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> oddPowerSliderAttachment, evenPowerSliderAttachment, evenMixSliderAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, String paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        slider.addListener(this);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationWindow)
};

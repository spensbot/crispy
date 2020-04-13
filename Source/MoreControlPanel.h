/*
  ==============================================================================

    MoreControlPanel.h
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
class MoreControlPanel    : public Component
{
public:
    MoreControlPanel(AudioProcessorValueTreeState& params) : parameters(params)
    {
//        addAndMakeVisible(oversamplingBox);
//        oversamplingBoxAttachment.reset(new ComboBoxAttachment(parameters, Constants::ID_OVERSAMPLING, oversamplingBox));
        
        initSlider(autoGainAmountSlider, autoGainAmountSliderAttachment, Constants::ID_AUTO_GAIN_AMOUNT);
        initSlider(oversamplingSlider, oversamplingSliderAttachment, Constants::ID_OVERSAMPLING);
        initSlider(dryGainSlider, dryGainSliderAttachment, Constants::ID_DRY_GAIN);
        dryGainSlider.setSliderStyle(Slider::LinearVertical);
        dryGainSlider.setPopupDisplayEnabled(true, true, this);
        initSlider(wetGainSlider, wetGainSliderAttachment, Constants::ID_WET_GAIN);
        wetGainSlider.setSliderStyle(Slider::LinearVertical);
        wetGainSlider.setPopupDisplayEnabled(true, true, this);
        initSlider(hpSlider, hpSliderAttachment, Constants::ID_HI_PASS_FREQ);
        hpSlider.setPopupDisplayEnabled(true, true, this);
        initSlider(lpSlider, lpSliderAttachment, Constants::ID_LOW_PASS_FREQ);
        lpSlider.setPopupDisplayEnabled(true, true, this);
        
        initLabel(autoGainLabel, &autoGainAmountSlider, "Auto-Gain");
        initLabel(oversamplingLabel, &oversamplingSlider, "Oversampling");
        initLabel(dryLabel, &dryGainSlider, "Dry");
        initLabel(wetLabel, &wetGainSlider, "Wet");
        
        addAndMakeVisible(hpIcon);
        addAndMakeVisible(lpIcon);
        hpIcon.setHP(true);
    }

    ~MoreControlPanel()
    {
        
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colour::fromHSV(0.0f, 0.0f, 0.4f, 0xff));
    }

    void resized() override
    {
        int padding = 5;
        int rotaryWidth = getWidth() / 3;
        int sliderWidth = 40;
        int centerGap = 50;
        
        Rectangle<int> bounds = getLocalBounds();
        bounds.reduce(padding, padding);
        
        bounds.removeFromTop(30);
        
        auto left = bounds.removeFromLeft(rotaryWidth);
        auto leftTop = left.removeFromTop(left.getHeight()/4);
        leftTop.removeFromRight(leftTop.getWidth() / 6);
        hpIcon.setBounds(leftTop.removeFromRight(leftTop.getWidth()/3));
        hpSlider.setBounds(leftTop);
        left.removeFromBottom(15);
        autoGainAmountSlider.setBounds(left.removeFromBottom(100));
        
        auto right = bounds.removeFromRight(rotaryWidth);
        auto rightTop = right.removeFromTop(right.getHeight()/4);
        rightTop.removeFromLeft(rightTop.getWidth() / 6);
        lpIcon.setBounds(rightTop.removeFromLeft(rightTop.getWidth()/3));
        lpSlider.setBounds(rightTop);
        right.removeFromBottom(15);
        oversamplingSlider.setBounds(right.removeFromBottom(100));
        //oversamplingBox.setBounds(right.removeFromBottom(right.getHeight()/2));
        
        int excess = bounds.getWidth() - 2*sliderWidth - centerGap;
        bounds.reduce(excess/2, 0);
        
        dryGainSlider.setBounds(bounds.removeFromLeft(sliderWidth));
        wetGainSlider.setBounds(bounds.removeFromRight(sliderWidth));
    }

private:
    AudioProcessorValueTreeState& parameters;
    
    Slider autoGainAmountSlider,
        oversamplingSlider,
        dryGainSlider,
        wetGainSlider,
        hpSlider,
        lpSlider;
    
    stm::FilterIcon hpIcon, lpIcon;
    
    Label autoGainLabel, oversamplingLabel, dryLabel, wetLabel;
    
    ComboBox oversamplingBox;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    std::unique_ptr<SliderAttachment> autoGainAmountSliderAttachment,
        oversamplingSliderAttachment,
        dryGainSliderAttachment,
        wetGainSliderAttachment,
        hpSliderAttachment,
        lpSliderAttachment;
    
    typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
    
    std::unique_ptr<ComboBoxAttachment> oversamplingBoxAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, String paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
    }
    
    void initLabel(Label& label, Component* owner, String text){
        label.setText(text, dontSendNotification);
        label.attachToComponent(owner, false);
        label.setJustificationType(Justification::centred);
        label.setFont(Font(24.0f));
        addAndMakeVisible(label);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoreControlPanel)
};

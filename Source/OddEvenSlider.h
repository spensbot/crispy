/*
  ==============================================================================

    OddEvenSlider.h
    Created: 7 Apr 2020 5:28:15pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CrispyLookAndFeel.h"

//==============================================================================
/*
*/
class OddEvenSlider    : public Component, public Slider::Listener
{
public:
    OddEvenSlider(Slider& s) : slider(s)
    {
        addChildAndSetID(&slider, "slider");
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        slider.addListener(this);
        addAndMakeVisible(&slider);
    }

    ~OddEvenSlider()
    {
    }

    void paint (Graphics& g) override
    {
        auto bounds = getLocalBounds();
        
        g.setColour (CrispyLookAndFeel::colourAccent);
        g.setFont (28.0f);
        g.drawText ("odd", bounds.removeFromLeft(textWidth),
                    Justification::centred, true);   // draw some placeholder text
        
        g.drawText ("even", bounds.removeFromRight(textWidth),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        textWidth = getWidth() / 5;
        slider.setBounds(bounds.reduced(textWidth, 0));
        repaint();
    }
    
    void sliderValueChanged (Slider *slider) override
    {
        //slider.getValue();
        repaint();
    }

private:
    Slider& slider;
    
    int textWidth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OddEvenSlider)
};

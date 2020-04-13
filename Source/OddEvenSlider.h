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
        
        float val = slider.getValue();
        
        auto baseColour = CrispyLookAndFeel::colourAccent;
        float minAlpha = 0.3f;
        float alphaRange = 1.0f - minAlpha;
        float evenAlpha = val * alphaRange + minAlpha;
        float oddAlpha = (1.0f - val) * alphaRange + minAlpha;
//        float maxS = baseColour.getSaturation();
//        float evenS = val * maxS;
//        float oddS = (1.0f - val ) * maxS;
        
        g.setFont (28.0f);
        g.setColour (baseColour.withAlpha(oddAlpha));
        g.drawText ("odd", bounds.removeFromLeft(textWidth),
                    Justification::centred, true);
        
        g.setColour (baseColour.withAlpha(evenAlpha));
        g.drawText ("even", bounds.removeFromRight(textWidth),
                    Justification::centred, true);
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
        repaint();
    }

private:
    Slider& slider;
    
    int textWidth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OddEvenSlider)
};

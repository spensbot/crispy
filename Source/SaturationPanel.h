/*
  ==============================================================================

    SaturationPanel.h
    Created: 6 Apr 2020 12:09:32am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"
#include "OddEvenSlider.h"
#include "SaturationVisualizer.h"
#include "CrispyLookAndFeel.h"

//==============================================================================
/*
*/
class SaturationPanel    : public Component, public Slider::Listener
{
public:
    SaturationPanel(AudioProcessorValueTreeState& params)
    : parameters(params)
    , oddEvenSliderLabeled(oddEvenSlider)
    {
        addAndMakeVisible(saturationVisualizer);
        
        addAndMakeVisible(saturationSlider);
        saturationSlider.setSliderStyle(Slider::RotaryVerticalDrag);
        saturationSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        saturationSlider.addListener(this);
        
        oddEvenSlider.addListener(this);
        addAndMakeVisible(oddEvenSliderLabeled);
        
        saturationSliderAttachment.reset(new SliderAttachment(parameters, Constants::ID_SATURATION, saturationSlider));
        oddEvenSliderAttachment.reset(new SliderAttachment(parameters, Constants::ID_ODD_EVEN_MIX, oddEvenSlider));
        
        addAndMakeVisible(moreControlButton);
        moreControlButton.setLookAndFeel(&moreControlButtonLookAndFeel);
        moreControlButton.setButtonText("MORE CONTROL");
        moreControlButton.setClickingTogglesState(true);
    }

    ~SaturationPanel()
    {
        
    }

    void paint (Graphics& g) override
    {
        auto bounds = getBounds().reduced(20, 10);

        g.setColour (CrispyLookAndFeel::colourAccent);
        g.setFont (50.0f);
        g.drawText ("Crispy", bounds, Justification::topLeft, true);
    }

    void resized() override
    {
        auto buttonHeight = 25;
        auto sliderHeight = getHeight() / 4 - buttonHeight;
        auto visualizerHeight = getHeight() / 2;
        
        Rectangle<int> bounds = getLocalBounds();
        
        moreControlButton.setBounds(bounds.removeFromBottom(buttonHeight));
        
        oddEvenSliderLabeled.setBounds(bounds.removeFromBottom(sliderHeight));
        
        auto visualizerRect = bounds.removeFromBottom(visualizerHeight);
        saturationVisualizer.setBounds(visualizerRect);
        
        auto padding = visualizerRect.getHeight()/7;
        saturationSlider.setBounds(visualizerRect.reduced(padding));
        
    }
    
    void sliderValueChanged (Slider *slider) override
    {
        saturationVisualizer.reset(oddEvenSlider.getValue(), saturationSlider.getValue());
        repaint();
    }

private:
    class MoreControlButtonLookAndFeel : public LookAndFeel_V4
    {
    public:
        MoreControlButtonLookAndFeel()
        {
            setColour (TextButton::textColourOffId, CrispyLookAndFeel::colourAccent);
            setColour (TextButton::textColourOnId, CrispyLookAndFeel::colourAccent);
        }
        
        void drawButtonBackground (Graphics& g, Button& button,const Colour& backgroundColour,
                                                   bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {}
    };
    
    AudioProcessorValueTreeState& parameters;
    SaturationVisualizer saturationVisualizer;
    Slider oddEvenSlider, saturationSlider;
    
    OddEvenSlider oddEvenSliderLabeled;
    
    DropShadow glow;
    
    TextButton moreControlButton;
    MoreControlButtonLookAndFeel moreControlButtonLookAndFeel;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> oddEvenSliderAttachment, saturationSliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationPanel)
};

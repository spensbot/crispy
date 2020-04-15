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
#include "SaturationVisualizerV2.h"
#include "CrispyLookAndFeel.h"
#include "Glow.h"

//==============================================================================
/*
*/
class SaturationPanel    : public Component, public Slider::Listener, public Button::Listener
{
public:
    SaturationPanel(AudioProcessorValueTreeState& params)
    : parameters(params)
    , oddEvenSliderLabeled(oddEvenSlider)
    {
        addAndMakeVisible(glow);
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
        
        updateMoreControlButton();
        moreControlButton.setClickingTogglesState(true);
        moreControlButton.addListener(this);
        moreControlButtonAttachment.reset(new ButtonAttachment(parameters, Constants::ID_MORE_CONTROL, moreControlButton));
        
        saturationVisualizer.reset(oddEvenSlider.getValue(), saturationSlider.getValue());
        
        updateVisualizer();
    }

    ~SaturationPanel()
    {
        
    }

    void paint (Graphics& g) override
    {
        auto bounds = getLocalBounds().reduced(10, 0);

        g.setColour (CrispyLookAndFeel::colourAccent);
        g.setFont (55.0f);
        g.drawText ("Crispy", bounds, Justification::topLeft, true);
    }

    void resized() override
    {
        auto buttonHeight = 25;
        auto sliderHeight = getHeight() / 4 - buttonHeight;
        auto visualizerHeight = getHeight() / 2;
        
        Rectangle<int> bounds = getLocalBounds();
        glow.setBounds(bounds);
        
        moreControlButton.setBounds(bounds.removeFromBottom(buttonHeight));
        
        oddEvenSliderLabeled.setBounds(bounds.removeFromBottom(sliderHeight));
        
        auto visualizerRect = bounds.removeFromBottom(visualizerHeight);
        saturationVisualizer.setBounds(visualizerRect);
        
        auto padding = visualizerRect.getHeight()/7;
        saturationSlider.setBounds(visualizerRect.reduced(padding));
        
    }
    
    void sliderValueChanged (Slider *slider) override
    {
        updateVisualizer();
        repaint();
    }
    
    void buttonClicked (Button *button) override
    {
        updateMoreControlButton();
    }

    TextButton moreControlButton;

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
    
    void updateVisualizer() {
        float odd = saturationSlider.getValue();
        float even = oddEvenSlider.getValue();
        saturationVisualizer.reset(even, odd);
        
        float glowSizeMin = 0.5f;
        float glowSizeMax = 0.7f;
        float glowAlphaMin = 0.5f;
        float glowAlphaMax = 0.8f;
        float glowSizeRange = glowSizeMax - glowSizeMin;
        float glowAlphaRange = glowAlphaMax - glowAlphaMin;
        
        float glowSize = glowSizeMin + glowSizeRange * odd;
        float glowAlpha = glowAlphaMin + glowAlphaRange * odd;
        
        glow.set(glowAlpha, glowSize, CrispyLookAndFeel::colourAccent);
    }
    
    void updateMoreControlButton() {
        bool isMoreControl = moreControlButton.getToggleState();
        if (isMoreControl){
            moreControlButton.setButtonText("KEEP IT SIMPLE");
        }
        else {
            moreControlButton.setButtonText("MORE CONTROL");
        }
    }
    
    AudioProcessorValueTreeState& parameters;
    SaturationVisualizer saturationVisualizer;
    Slider oddEvenSlider, saturationSlider;
    
    OddEvenSlider oddEvenSliderLabeled;
    
    MoreControlButtonLookAndFeel moreControlButtonLookAndFeel;
    
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    std::unique_ptr<ButtonAttachment> moreControlButtonAttachment;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> oddEvenSliderAttachment, saturationSliderAttachment;
    
    Glow glow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationPanel)
};

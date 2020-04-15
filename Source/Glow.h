/*
  ==============================================================================

    Glow.h
    Created: 14 Apr 2020 4:48:19pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Glow    : public Component
{
public:
    Glow()
    {
    }

    ~Glow()
    {
    }
    
    /**Size is the proportion of the height that the gradient takes up*/
    void set(float _alpha, float _size, Colour _colour){
        colour = _colour;
        size = _size;
        alpha = _alpha;
        repaint();
    }

    void paint (Graphics& g) override
    {
        auto glowColourStart = colour.withAlpha(alpha);
        auto glowColourEnd = colour.withAlpha(0.0f);
        
        float xCenter = float (getWidth()/2);
        float yCenter = float (getHeight()/2);
        Point<float> glowStart = {xCenter, yCenter};
        Point<float> glowEnd = {xCenter, yCenter * (1.0f + size)};
        
        ColourGradient gradient = ColourGradient(glowColourStart, glowStart, glowColourEnd, glowEnd, true);
        g.setGradientFill(gradient);
        g.fillAll();
    }

    void resized() override
    {
        
    }

private:
    float size = 1.0f;
    float alpha = 1.0f;
    Colour colour = Colours::white;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Glow)
};

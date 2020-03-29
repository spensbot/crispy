/*
  ==============================================================================

    CsLookAndFeel.h
    Created: 26 Mar 2020 6:31:55am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class LooknFeel : public LookAndFeel_V4
{
public:
    LooknFeel()
    {
        
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        // fill
        g.setColour (Colour::fromHSV(0.0f, 0.0f, 0.5f, 0.7f));
        g.fillEllipse (rx, ry, rw, rw);
        
        Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        // pointer
        g.setColour (Colours::yellow);
        g.fillPath (p);
    }
    
//    void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider& slider) override
//    {
//        float padding = 5.0f;
//        float fx = (float)x;
//        float fy = (float)y;
//        float fwidth = (float)width;
//        float fheight = (float)height;
//
//        //background
//        g.setColour(Colour::fromHSV(0.0f, 0.0f, 0.5f, 0.5f));
//        g.fillRoundedRectangle(fx, fy, fwidth, fheight, padding * 2);
//
//        //track
//        g.setColour(Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.5f));
//        g.fillRoundedRectangle(fx + padding, fy + fwidth/2 - padding, padding * 2, height - padding * 2, padding);
//
//        //handle
//        g.setColour(Colours::whitesmoke);
//        g.fillRoundedRectangle(fx + padding, sliderPos, fwidth - padding * 2, padding * 2, padding);
//    }
    
private:
    
};

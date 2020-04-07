/*
  ==============================================================================

    DecibelSlider.h
    Created: 25 Oct 2019 4:00:20pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DecibelSlider : public Slider
{
public:
    
    String getTextFromValue (double value) override
    {
        return Decibels::toString(value);
    }
    
    double getValueFromText (const String& text) override
    {
        auto decibelText = text.upToFirstOccurrenceOf ("dB", false, false).trim();
        auto minusInfinitydB = -100.0;
        return decibelText.equalsIgnoreCase ("-INF") ? minusInfinitydB : decibelText.getDoubleValue();
    }
    
};

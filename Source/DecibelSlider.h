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
    String getTextFromValue (double value) override;
    double getValueFromText (const String& text) override;
private:
};

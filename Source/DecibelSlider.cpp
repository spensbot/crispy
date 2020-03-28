/*
  ==============================================================================

    DecibelSlider.cpp
    Created: 25 Oct 2019 4:00:20pm
    Author:  Spenser Saling

  ==============================================================================
*/

#include "DecibelSlider.h"

String DecibelSlider::getTextFromValue (double value){
    return Decibels::toString(value);
}

double DecibelSlider::getValueFromText (const String& text){
    auto decibelText = text.upToFirstOccurrenceOf ("dB", false, false).trim();
    auto minusInfinitydB = -100.0;
    return decibelText.equalsIgnoreCase ("-INF") ? minusInfinitydB : decibelText.getDoubleValue();
}

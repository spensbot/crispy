/*
  ==============================================================================

    BufferDrawer.h
    Created: 25 Nov 2019 10:38:28am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class BufferDrawer    : public Component, private Timer
{
public:
    enum Type {max, rms};
    BufferDrawer(AudioBuffer<float>& buffer);
    ~BufferDrawer();

    void paint (Graphics&) override;
    void resized() override;
    void setWindow(int startSample, int numSamples);
    void setSpacing(int _gap, int _lineWidth);
    
    void timerCallback () override;
    
    Type type = rms;

private:
    AudioBuffer<float>& buffer;
    int startSample = 0;
    int numSamples = 0;
    int gap = 0;
    int lineWidth = 1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BufferDrawer)
};

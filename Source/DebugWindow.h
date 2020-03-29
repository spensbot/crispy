/*
  ==============================================================================

    Debugger.h
    Created: 28 Mar 2020 8:52:40am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class DebugWindow : public Component, private Timer
{
public:
    static const int numDebugLines = 30;
    inline static String debugLines[30];
    
    DebugWindow()
    {
        startTimerHz(15);
        for(int i=0 ; i<numDebugLines ; i++){
            debugLines[i] = "";
        }
        debugLines[0] = "Debug Messages:";
    }

    ~DebugWindow()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colours::darkgrey);
        g.setColour (Colours::white);
        g.setFont(12.0f);
        Rectangle<int> bounds = getLocalBounds();
        bounds.reduce(5, 5);
        
        int lineHeight = 15;
        for (int line=0 ; line<numDebugLines ; line++){
            g.drawText(debugLines[line], bounds.removeFromTop(lineHeight), Justification::left, true);
        }
    }

    void resized() override
    {
        
    }
    
    void timerCallback() override {
        repaint();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebugWindow)
};

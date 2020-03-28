/*
  ==============================================================================

    SaturationVisualizer.h
    Created: 25 Mar 2020 5:34:51pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CrispySaturator.h"

//==============================================================================
/*
*/
class SaturationVisualizer    : public Component
{
public:
    SaturationVisualizer()
    {
        
    }

    ~SaturationVisualizer()
    {
        
    }
    
    void reset (float _saturation) {
        saturation = _saturation;
        updateBuffer();
    }

    void paint (Graphics& g) override
    {
        int height = getHeight();
        int steps = buffer.getNumSamples();
        float pos = 0.0f;
        auto* bufferPointer = buffer.getReadPointer(0);
        
        g.setColour (Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
        
        for (int step=0 ; step<steps ; step++){
            float sample = bufferPointer[step];
            float startY = (float)height;
            float endY = startY - (float)height * sample;

            g.drawLine(pos, startY, pos, endY, 1.0f);
            
            pos += 1;
        }
    }

    void resized() override
    {
        buffer.setSize(1, getWidth());
        updateBuffer();
    }
    
    void updateBuffer(){
        int numSamples = buffer.getNumSamples();
        for (int sample=0 ; sample < numSamples ; sample++){
            float value = (float)sample / (float)numSamples;
            float saturatedValue = CrispySaturator::saturateSample(value, saturation);
            buffer.setSample(0, sample, saturatedValue);
        }
    }

private:
    AudioSampleBuffer buffer;
    float saturation = 1.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationVisualizer)
};

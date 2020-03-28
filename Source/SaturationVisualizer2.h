/*
  ==============================================================================

    SaturationVisualizer2.h
    Created: 26 Mar 2020 3:51:23pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SaturationVisualizer2    : public Component
{
public:
    SaturationVisualizer2()
    {
        
    }

    ~SaturationVisualizer2()
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
        float y0 = (float)height / 2;
        float yMax = y0;
        
        
        g.setColour (Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
        auto* bufferPointer = buffer.getReadPointer(0);
        
        for (int step=0 ; step<steps ; step++){
            float sample = bufferPointer[step];
            float y = y0 + sample * yMax;

            g.drawLine(pos, y0, pos, y, 1.0f);
            
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
        float radsPerSample = MathConstants<double>::twoPi / (float) numSamples;
        float pos = 0.0f;
        
        for (int sample=0 ; sample < numSamples ; sample++){
            float value = std::sin(pos);
            float saturatedValue = CrispySaturator::saturateSample(value, saturation);
            buffer.setSample(0, sample, saturatedValue);
            
            pos += radsPerSample;
        }
    }

private:
    AudioSampleBuffer buffer;
    float saturation = 1.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationVisualizer2)
};

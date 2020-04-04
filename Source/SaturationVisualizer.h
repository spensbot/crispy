/*
  ==============================================================================

    SaturationVisualizer.h
    Created: 26 Mar 2020 3:51:23pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

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
    
    void reset (float _odd, float _even, bool _evenSmooth)
    {
        odd = _odd;
        even = _even;
        evenSmooth = _evenSmooth;
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

private:
    AudioSampleBuffer buffer;
    
    const float startAngle = -MathConstants<float>::pi;
    const float length = MathConstants<float>::twoPi;
    
    float odd = 1.0f;
    float even = 0.0f;
    bool evenSmooth = true;
    
    stm::SaturatorCrispyOdd saturatorOdd;
    stm::SaturatorCrispyEven saturatorEven;
    
    void updateBuffer(){
        int numSamples = buffer.getNumSamples();
        float radsPerSample = length / (float) numSamples;
        float pos = startAngle;
        
        for (int sample=0 ; sample < numSamples ; sample++){
            float value = std::sin(pos);
            float saturatedValue = saturatorEven.saturateSample(value, even);
            saturatedValue = saturatorOdd.saturateSample(saturatedValue, odd);
//            float saturatedValue = saturatorOdd.saturateSample(value, odd);
//            saturatedValue = saturatorEven.saturateSample(saturatedValue, even);
            buffer.setSample(0, sample, saturatedValue);
            
            pos += radsPerSample;
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationVisualizer)
};

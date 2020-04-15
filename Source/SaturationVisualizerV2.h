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
    
    void reset (float evenMix, float oddPower)
    {
        saturator.setEven(evenMix);
        saturator.setOdd(oddPower);
        updateBuffer();
    }

    void paint (Graphics& g) override
    {
        int height = getHeight();
        int numSamples = buffer.getNumSamples();
        float pos = float (startX);
        float y0 = float (height / 2);
        float yMax = y0 - float(dotRadius);
        
        g.setColour (Colour::fromHSV(0.0f,0.0f,0.5f,1.0f));
        auto* bufferPointer = buffer.getReadPointer(0);
        
        for (int i=0 ; i<numSamples ; i++){
            //            float sample = bufferPointer[i];
            //            float y = y0 + sample * yMax;
            
            //            g.drawLine(pos, y0, pos, y, 2.0f);
            //            g.fillEllipse(pos - dotRadius, y - dotRadius, dotRadius * 2, dotRadius * 2);
            //            g.drawLine(pos, y - 5, pos, y + 5, float(dotRadius));
            
            pos += float(cc);
        }
        
        g.setColour (Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
        
        pos = float (startX);
        for (int i=0 ; i<numSamples-1 ; i++){
            float y = y0 + bufferPointer[i] * yMax;
            float nextY = y0 + bufferPointer[i+1] * yMax;
            float nextPos = pos + float(cc);
            
            g.drawLine(pos, y, nextPos, nextY, 2.0f);
            
            pos = nextPos;
        }
    }

    void resized() override
    {
        int useableWidth = getWidth() - 2 * dotRadius;
        int numSteps = useableWidth / cc;
        int numDots = numSteps + 1;
        
        int leftover = useableWidth - numSteps * cc;
        startX = dotRadius + leftover / 2;
        
        buffer.setSize(1, numDots);
        updateBuffer();
    }

private:
    const int dotRadius = 1;
    const int cc = 1;
    const float startAngle = -MathConstants<float>::pi;
    const float length = MathConstants<float>::twoPi;
    
    int startX = 0;
    
    AudioSampleBuffer buffer;
    
    stm::SaturatorCrispy saturator;
    
    void updateBuffer(){
        int numSamples = buffer.getNumSamples();
        int numSteps = numSamples - 1;
        float radsPerStep = length / float (numSteps);
        float pos = startAngle;
        
        for (int sample=0 ; sample < numSamples ; sample++){
            float value = std::sin(pos);
            buffer.setSample(0, sample, saturator.saturateSample(value));
            
            pos += radsPerStep;
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationVisualizer)
};


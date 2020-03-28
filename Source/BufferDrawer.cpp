/*
  ==============================================================================

    BufferDrawer.cpp
    Created: 25 Nov 2019 10:38:28am
    Author:  Spenser Saling

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BufferDrawer.h"

//==============================================================================
BufferDrawer::BufferDrawer(AudioBuffer<float>& _buffer)
:buffer(_buffer)
{
    startTimerHz(30);
}

BufferDrawer::~BufferDrawer()
{
}

void BufferDrawer::paint (Graphics& g)
{
    //g.fillAll (Colours::black);
    
    int height = getHeight();
    float center = height/2.0f;
    int width = getWidth();
    
    int samplesPerPixel = (numSamples>0 ? numSamples : buffer.getNumSamples()) / width;
    int nextStartSample = startSample;
    int increment = gap + lineWidth;
    
    for (int pixel=0 ; pixel<width ; pixel += increment){
        
        float peak;
        switch (type) {
            case rms:
                peak = buffer.getRMSLevel(0, nextStartSample, samplesPerPixel * increment);
                break;
            case max:
                peak = buffer.getMagnitude(nextStartSample, samplesPerPixel * increment);
                break;
        }
        
        float length = peak * center * 2.0f;
        float startY = center - length/2.0f;
        //float endY = startY + length * 2;
        g.setColour (Colour::fromHSV((float)pixel/(float)width, 1.0, 1.0, 1.0));
        g.fillRect((float)pixel, startY, (float)lineWidth, length);
        
        nextStartSample += samplesPerPixel * increment;
    }

}

void BufferDrawer::resized()
{
    
}

void BufferDrawer::setWindow(int _startSample, int _numSamples){
    startSample = _startSample;
    numSamples = _numSamples;
}

void BufferDrawer::timerCallback() {
    repaint();
}

void BufferDrawer::setSpacing(int _gap, int _lineWidth){
    gap = _gap;
    lineWidth = _lineWidth;
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

//==============================================================================
CrispySaturatorAudioProcessorEditor::CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
,parameters(p.parameters)
,inBufferDrawer(p.crispyEngine.inBuffer.buffer)
,outBufferDrawer(p.crispyEngine.outBuffer.buffer)
,saturationWindow(parameters)
,moreControlWindow(parameters)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(true, true);
    setResizeLimits(300, 300, 1920, 1080);
    setSize (600, 400);
    
    setLookAndFeel(&looknFeel);
    
    addAndMakeVisible(inGainSlider);
    addAndMakeVisible(outGainSlider);
    addAndMakeVisible(inBufferDrawer);
    addAndMakeVisible(outBufferDrawer);
    addAndMakeVisible(saturationWindow);
    addAndMakeVisible(debugWindow);
    addAndMakeVisible(moreControlWindow);
    
    inGainSlider.setSliderStyle(Slider::LinearVertical);
    inGainSlider.setPopupDisplayEnabled(true, true, this);
    inGainSlider.setPopupMenuEnabled(true);
    inGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    outGainSlider.setSliderStyle(Slider::LinearVertical);
    outGainSlider.setPopupDisplayEnabled(true, true, this);
    outGainSlider.setPopupMenuEnabled(true);
    outGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    inGainSliderAttachment.reset(new SliderAttachment(p.parameters, Constants::ID_IN_GAIN, inGainSlider));
    outGainSliderAttachment.reset(new SliderAttachment(p.parameters, Constants::ID_OUT_GAIN, outGainSlider));
}

CrispySaturatorAudioProcessorEditor::~CrispySaturatorAudioProcessorEditor()
{
}

//==============================================================================
void CrispySaturatorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void CrispySaturatorAudioProcessorEditor::resized()
{
    int sliderWidth = 30;
    int bufferHeight = getHeight()/4;
    
    Rectangle<int> bounds = getLocalBounds();
    
    if (processor.debug){
        debugWindow.setBounds(bounds.removeFromLeft(getWidth() * 0.2));
    }
    
    moreControlWindow.setBounds(bounds.removeFromRight(getWidth() * 0.2));
    
    Rectangle<int> upperBounds = bounds.removeFromTop(bufferHeight);
    Rectangle<int> lowerBounds = bounds.removeFromBottom(bufferHeight);
    inGainSlider.setBounds(upperBounds.removeFromLeft(sliderWidth));
    outGainSlider.setBounds(lowerBounds.removeFromLeft(sliderWidth));
    inBufferDrawer.setBounds(upperBounds);
    outBufferDrawer.setBounds(lowerBounds);
    
//    inGainSlider.setBounds(bounds.removeFromLeft(sliderWidth));
//    outGainSlider.setBounds(bounds.removeFromRight(sliderWidth));
    
    //bounds.reduce(padding, padding);
    
    saturationWindow.setBounds(bounds);
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CrispySaturatorAudioProcessorEditor::CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
,inBufferDrawer(p.crispyEngine.inBuffer.buffer)
,outBufferDrawer(p.crispyEngine.outBuffer.buffer)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(true, true);
    setResizeLimits(300, 300, 1920, 1080);
    setSize (600, 400);
    
    setLookAndFeel(&csLookAndFeel);
    
    addAndMakeVisible(inGainSlider);
    addAndMakeVisible(outGainSlider);
    addAndMakeVisible(inBufferDrawer);
    addAndMakeVisible(outBufferDrawer);
    addAndMakeVisible(saturationVisualizer);
    addAndMakeVisible(saturationSlider);
    
    inGainSlider.setSliderStyle(Slider::LinearVertical);
    inGainSlider.setPopupDisplayEnabled(true, true, this);
    inGainSlider.setPopupMenuEnabled(true);
    inGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    outGainSlider.setSliderStyle(Slider::LinearVertical);
    outGainSlider.setPopupDisplayEnabled(true, true, this);
    outGainSlider.setPopupMenuEnabled(true);
    outGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    saturationSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    saturationSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    saturationSlider.addListener(this);
    
    inGainSliderAttachment.reset(new SliderAttachment(p.parameters, "inGain", inGainSlider));
    outGainSliderAttachment.reset(new SliderAttachment(p.parameters, "outGain", outGainSlider));
    saturationSliderAttachment.reset(new SliderAttachment(p.parameters, "saturation", saturationSlider));
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
    int padding = 30;
    int sliderWidth = 30;
    int bufferHeight = getHeight()/4;
    
    Rectangle<int> bounds = getLocalBounds();
    
    Rectangle<int> upperBounds = bounds.removeFromTop(bufferHeight);
    Rectangle<int> lowerBounds = bounds.removeFromBottom(bufferHeight);
    inGainSlider.setBounds(upperBounds.removeFromLeft(sliderWidth));
    outGainSlider.setBounds(lowerBounds.removeFromLeft(sliderWidth));
    inBufferDrawer.setBounds(upperBounds);
    outBufferDrawer.setBounds(lowerBounds);
    
//    inGainSlider.setBounds(bounds.removeFromLeft(sliderWidth));
//    outGainSlider.setBounds(bounds.removeFromRight(sliderWidth));
    
    saturationVisualizer.setBounds(bounds);
    
    //bounds.reduce(padding, padding);
    
    saturationSlider.setBounds(bounds);
}

void CrispySaturatorAudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    if (slider == &saturationSlider) {
        saturationVisualizer.reset(slider->getValue());
    }
}

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CrispySaturatorAudioProcessorEditor::CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor& p)
: AudioProcessorEditor (&p)
,processor (p)
,parameters(p.parameters)
,saturationPanel(parameters)
,moreControlPanel(parameters)
{
    bypass = parameters.getRawParameterValue(Params::ID_BYPASS);
    moreControl = parameters.getRawParameterValue(Params::ID_MORE_CONTROL);
    
    setLookAndFeel(&crispyLookAndFeel);
    
    addAndMakeVisible(saturationPanel);
    addAndMakeVisible(moreControlPanel);
    addAndMakeVisible(debugDisplay);
    addAndMakeVisible(bypassedVeil);
    
    addAndMakeVisible(matchedBypassButton);
    matchedBypassButton.setButtonText("MATCHED BYPASS");
    matchedBypassButton.setClickingTogglesState(true);
    matchedBypassButtonAttachment.reset(new ButtonAttachment(parameters, Params::ID_BYPASS, matchedBypassButton));
    matchedBypassButton.addListener(this);
    saturationPanel.moreControlButton.addListener(this);
    
    updateWindow();
}

CrispySaturatorAudioProcessorEditor::~CrispySaturatorAudioProcessorEditor()
{
    matchedBypassButton.removeListener(this);
    saturationPanel.moreControlButton.removeListener(this);
    setLookAndFeel(nullptr);
}

//==============================================================================
void CrispySaturatorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void CrispySaturatorAudioProcessorEditor::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    if(debug){
        debugDisplay.setBounds(bounds.removeFromLeft(debugWidth));
    }
    
    bypassedVeil.setBounds(bounds);
    
    saturationPanel.setBounds(bounds.removeFromTop(saturationHeight));
    moreControlPanel.setBounds(bounds);
    
    int bypassWidth = 80;
    int bypassHeight = 40;
    int excessWidth = bounds.getWidth() - bypassWidth;
    bounds.reduce(excessWidth/2, 40);
    bounds.removeFromTop(bounds.getHeight() - bypassHeight);
    matchedBypassButton.setBounds(bounds);
}

void CrispySaturatorAudioProcessorEditor::buttonClicked (Button *button)
{
    updateWindow();
}

void CrispySaturatorAudioProcessorEditor::updateWindow()
{
    int height = saturationHeight;
    int width = mainWidth;
    
    if (debug) {
        width += debugWidth;
    }
    
    Boolean isBypassed = matchedBypassButton.getToggleState();
    Boolean isMoreControl = saturationPanel.moreControlButton.getToggleState();
    
    if (isBypassed) {
        bypassedVeil.setVisible(true);
    } else {
        bypassedVeil.setVisible(false);
    }
    
    if (isMoreControl) {
        moreControlPanel.setEnabled(true);
        height += moreControlHeight;
    } else {
        moreControlPanel.setEnabled(false);
    }
    
    setSize(width, height);
    
    repaint();    
}

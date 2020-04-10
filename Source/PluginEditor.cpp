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
    bypass = parameters.getRawParameterValue(Constants::ID_BYPASS);
    moreControl = parameters.getRawParameterValue(Constants::ID_MORE_CONTROL);
    
    setLookAndFeel(&crispyLookAndFeel);
    
    addAndMakeVisible(saturationPanel);
    addAndMakeVisible(moreControlPanel);
    addAndMakeVisible(debugDisplay);
    addAndMakeVisible(bypassedVeil);
    
    addAndMakeVisible(matchedBypassButton);
    matchedBypassButton.setButtonText("MATCHED BYPASS");
    matchedBypassButton.setClickingTogglesState(true);
    matchedBypassButtonAttachment.reset(new ButtonAttachment(parameters, Constants::ID_BYPASS, matchedBypassButton));
    matchedBypassButton.addListener(this);
    saturationPanel.moreControlButton.addListener(this);
    
    updateWindow();
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
//    int bypassWidth = 80;
//    int bypassHeight = 35;
    
    Rectangle<int> bounds = getLocalBounds();
    
    if(debug){
        debugDisplay.setBounds(bounds.removeFromLeft(debugWidth));
    }
    
    bypassedVeil.setBounds(bounds);
    
    saturationPanel.setBounds(bounds.removeFromTop(saturationHeight));
    moreControlPanel.setBounds(bounds);
    
    int bypassWidth = 80;
    int remove = getWidth() - bypassWidth;
    bounds.reduce(remove/2, 30);
    bounds.removeFromTop(100);
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
    
    stm::DebugDisplay::add(11, "Processor Params:");
    stm::DebugDisplay::add(12, "*bypass: " + String(*bypass));
    stm::DebugDisplay::add(13, "*moreControl: " + String(*moreControl));
    
    stm::DebugDisplay::add(11, "Button Toggle State:");
    stm::DebugDisplay::add(12, "Bypass: " + String(isBypassed));
    stm::DebugDisplay::add(13, "More Control: " + String(isMoreControl));
    
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

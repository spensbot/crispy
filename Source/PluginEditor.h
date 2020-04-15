#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SaturationPanel.h"
#include "MoreControlPanel.h"
#include "Constants.h"
#include "CrispyLookAndFeel.h"

//==============================================================================
/**
*/
class CrispySaturatorAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener
{
public:
    CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor&);
    ~CrispySaturatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked (Button *button) override;

private:
    const bool debug = false;
    const int mainWidth = 400;
    const int debugWidth = 200;
    const float saturationHeightRatio = 1.0;
    const float moreControlHeightRatio = 0.63;
    const int saturationHeight = int ( mainWidth * saturationHeightRatio );
    const int moreControlHeight = int ( mainWidth * moreControlHeightRatio );
    
    CrispyLookAndFeel crispyLookAndFeel;
    
    CrispySaturatorAudioProcessor& processor;
    AudioProcessorValueTreeState& parameters;
    
    std::atomic<float>* bypass;
    std::atomic<float>* moreControl;
    
    SaturationPanel saturationPanel;
    MoreControlPanel moreControlPanel;
    
    stm::DisabledVeil bypassedVeil;
    
    TextButton matchedBypassButton;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    std::unique_ptr<ButtonAttachment> matchedBypassButtonAttachment;
    
    stm::DebugDisplay debugDisplay;
    
    void updateWindow();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrispySaturatorAudioProcessorEditor)
};

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
class CrispySaturatorAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    CrispySaturatorAudioProcessorEditor (CrispySaturatorAudioProcessor&);
    ~CrispySaturatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    CrispyLookAndFeel crispyLookAndFeel;
    
    CrispySaturatorAudioProcessor& processor;
    AudioProcessorValueTreeState& parameters;
    
    SaturationPanel saturationPanel;
    MoreControlPanel moreControlPanel;
    
    stm::DisabledVeil bypassedVeil;
    
    stm::DebugDisplay debugDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrispySaturatorAudioProcessorEditor)
};

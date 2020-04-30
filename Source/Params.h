/*
  ==============================================================================

    Parameters.h
    Created: 23 Apr 2020 5:40:02pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Params
{
public:
    inline static const String
        ID_SATURATION = "saturation",
        ID_ODD_EVEN_MIX = "oddEvenMix",
        ID_LOW_PASS_FREQ = "lowPassFreq",
        ID_HI_PASS_FREQ = "hiPassFreq",
        ID_AUTO_GAIN_AMOUNT = "autoGainAmount",
        ID_OVERSAMPLING = "oversampling",
        ID_DRY_GAIN = "dryGain",
        ID_WET_GAIN = "wetGain",
        ID_BYPASS = "bypass",
        ID_MORE_CONTROL = "moreControl"
        ;

    static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<RangedAudioParameter>> params;
        
        auto frequencyRange = NormalisableRange<float>(20.0f, 20000.0f, 0.1f);
        frequencyRange.setSkewForCentre(640.0f);
        
        auto gainRange = NormalisableRange<float>(-100.0f, 12.0f, 0.1f);
        gainRange.setSkewForCentre(-12.0f);
        
        auto oversamplingRange = NormalisableRange<float>(0.0f, 4.0, 1.0f);
        
        params.push_back( std::make_unique<AudioParameterFloat> (ID_SATURATION, "Saturation", 0.0f, 1.0f, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat> (ID_ODD_EVEN_MIX, "Odd/Even Mix", 0.0f, 1.0f, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat> (ID_LOW_PASS_FREQ, "Low Pass Frequency", frequencyRange, 20000.0f) );
        params.push_back( std::make_unique<AudioParameterFloat> (ID_HI_PASS_FREQ, "High Pass Frequency", frequencyRange, 20.0f) );
        params.push_back( std::make_unique<AudioParameterFloat> (ID_AUTO_GAIN_AMOUNT, "Auto Gain Amount", 0.0f, 1.0f, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat> (ID_OVERSAMPLING, "Oversampling", oversamplingRange, 1.0f) );
        params.push_back( std::make_unique<AudioParameterFloat> (ID_WET_GAIN, "Wet Gain", gainRange, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat> (ID_DRY_GAIN, "Dry Gain", gainRange, -100.0f) );
        params.push_back( std::make_unique<AudioParameterBool> (ID_BYPASS, "Bypass", false) );
        params.push_back( std::make_unique<AudioParameterBool> (ID_MORE_CONTROL, "More Control", true) );
        
        return { params.begin(), params.end() };
    }
};

/*
  ==============================================================================

    Constants.h
    Created: 28 Mar 2020 6:58:32am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Constants {
public:
    
    inline static const String
        ID_IN_GAIN = "inGain",
        ID_LOW_PASS_FREQ = "lowPassFreq",
        ID_HI_PASS_FREQ = "hiPassFreq",
        ID_NORMALIZE_ATTACK = "normalizeAttack",
        ID_NORMALIZE_RELEASE = "normalizeRelease",
        ID_NORMALIZE_AMOUNT = "normalizeAmount",
        ID_ODD = "odd",
        ID_EVEN = "even",
        ID_EVEN_SMOOTH = "evenSmooth",
        ID_WET_DRY = "wetDry",
        ID_OUT_GAIN = "outGain";
    
};

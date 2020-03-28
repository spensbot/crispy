/*
  ==============================================================================

    RamperLinear.h
    Created: 19 Nov 2019 5:11:32pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once
#include "RamperBase.h"
#include <math.h>

class RamperLinear : public RamperBase {
public:
    
    float getNext() override {
        if (current != target){
            
            float direction = (target > current) ? 1.0f : -1.0f;
            
            if (fabs(target-current) < delta){
                current = target;
            } else {
                current += delta * direction;
            }
                
        }
        return current;
    };

};

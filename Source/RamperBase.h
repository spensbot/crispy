/*
  ==============================================================================

    RamperBase.h
    Created: 19 Nov 2019 5:11:21pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

class RamperBase {
public:
    virtual ~RamperBase(){};
    
    void initialize(float _current, float _delta){
        current = _current;
        target = current;
        delta = _delta;
    }
    
    void updateTarget(float newTarget){
        target = newTarget;
    };
    
    virtual float getNext()=0;
    
protected:
    float current, target, delta;
};

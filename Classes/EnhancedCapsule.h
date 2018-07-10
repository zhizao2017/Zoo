//
//  EnhancedCapsule.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/31.
//
//

#ifndef EnhancedCapsule_h
#define EnhancedCapsule_h

#include <stdio.h>
#include "cocos2d.h"
#include "Capsule.h"
#include "Transistor.h"

class EnhancedCapsule: public Capsule {
public:
    EnhancedCapsule(){};
    ~EnhancedCapsule(){};
    
    static EnhancedCapsule *CreateSpriteWithFrame(const char *name);
    
    CREATE_FUNC(EnhancedCapsule);
    
    void InitEnhancdCapsule();
    
    void update(float delta);
    
    void SniffAppearPosition(cocos2d::Map<int, Transistor*> *transistorSet);
    
    void LiveMethod(float delta);
    
private:
    float metric;
    cocos2d::Vec2 appearPosition;
    
    float lifeCycle;
};

#endif /* EnhancedCapsule_h */

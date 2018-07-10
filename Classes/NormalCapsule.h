//
//  NormalCapsule.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/30.
//
//

#ifndef NormalCapsule_h
#define NormalCapsule_h

#include <stdio.h>
#include "cocos2d.h"
#include "Capsule.h"
#include "Define.h"

class NormalCapsule:public Capsule {
public:
    NormalCapsule(){};
    ~NormalCapsule(){};

    static NormalCapsule *CreateSpriteWithFrame(const char *name);
    
    CREATE_FUNC(NormalCapsule);
    
    void InitNormalCapsule();
    
    void update(float delta);
    
    void LiveMethod(float delta);
    void Flying();
private:
    float metric;
    float lifeCycle;
};

#endif /* NormalCapsule_h */
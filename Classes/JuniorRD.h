//
//  JuniorRD.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/30.
//
//

#ifndef JuniorRD_h
#define JuniorRD_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"
#include "NormalCapsule.h"

class JuniorRD: public cocos2d::Sprite {
public:
    JuniorRD(){};
    ~JuniorRD(){};
    
    static JuniorRD *CreateJuniorRDSprite();
    
    void SetCapsule(NormalCapsule* capsule){this->normalCapsule = capsule;};
    
    CREATE_FUNC(JuniorRD);
    
private:
    
    void InitJuniorRDSprite();
    
    NormalCapsule *normalCapsule;
};

#endif /* JuniorRD_h */

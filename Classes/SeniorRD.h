//
//  SeniorRD.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/30.
//
//

#ifndef SeniorRD_h
#define SeniorRD_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"

class SeniorRD: public cocos2d::Sprite {
public:
    SeniorRD(){};
    ~SeniorRD(){};
    
    static SeniorRD *CreateSeniorRDSprite();
    
    CREATE_FUNC(SeniorRD);
private:
    
    void InitSeniorRDSprite();
};

#endif /* SeniorRD_h */

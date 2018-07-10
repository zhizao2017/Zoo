//
//  Transistor.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/20.
//
//

#ifndef Transistor_h
#define Transistor_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"

class Transistor: public cocos2d::Sprite {

public:
    Transistor(){};
    ~Transistor(){};
    
    static Transistor *CreateTransistorSprite();
    
    CREATE_FUNC(Transistor);
    
    void CrashEdge1();
    void CrashEdge2();
    void CrashEdge3();
    void CrashEdge4();
    
    void InitSpeed();
    
    void changeV(cocos2d::Vec2 heroPosition);
    
    bool IsAlive(){return available;};
    void Dead(){ available = false; }
    
    void SetTransistorType(transistorType t){type = t;};
    transistorType GetTransistorType(){return type;};
    
    void liveMethod(float delta);
    
    void AppearAction();
    void Activity(){this->edible = true;};
    bool IsEdible(){return edible;};
    
    void PerformBounsAnimation();
    void PerformPunishAnimation();
    void PunishAnimationEnd();
    void BounsAnimationEnd();
    void TargetAnimationEnd();
    
    void SetTarget(transistorType type){target = type;};
    
    void targetTips(float delta);
    cocos2d::Size GetTransistorSize(){return transistor->getContentSize();};

private:
    void InitTransistorSprite();
    
    cocos2d::Vec2 velocity;
    bool available;
    bool edible;
    bool isInTarget;
    
    float baseVelocity;
    float lifeCycle;
    
    transistorType type;
    transistorType target;
    
    cocos2d::Label *bounusPunishLabel;
    cocos2d::Sprite *transistor;
};

#endif /* Transistor_h */

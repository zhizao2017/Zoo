//
//  Hero.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#ifndef Hero_h
#define Hero_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"
#include "SlideDirection.h"
#include "AnimationType.h"
#include "SimpleAudioEngine.h"

enum HeroStatus {
    HAwait = 0,
    HMoving,
    HEating,
    HLaughing,
    HCrying
};

class Hero: public cocos2d::Sprite {
public:
    Hero(){};
    ~Hero(){};
    
    static Hero *CreateSpriteWithFrame(const char * name);
    void InitHero();
    void InitHeroAnimation();
    cocos2d::Animation *CreateAnimation(const char *resourcePath, const char *prefix, int frameCount, float delay, bool isLoops);
    
    CREATE_FUNC(Hero);
    void SetPreviousTouchPoint(cocos2d::Vec2 point){this->previousTouchPoint = point;};
    
    void update(float delta);

    void MoveTo(cocos2d::Vec2 currentPoint);
    void DoCrying();
    void DoEating(bool isBonus);
    void DoLaughing();
    
    void SetStatus(HeroStatus status){this->status = status;};
    HeroStatus GetStatus() const{return status;};
    void ResetStatus();
    
    void PerformAction(cocos2d::Animate *action, bool isBouns);
    
    bool IsPunished(){return isPunished;};
    void BePunished(){isPunished = true;};
    
    void CrashEdge();
    
private:
    HeroStatus status;
    
    cocos2d::PhysicsBody *physicsBody;
    
    bool isDelete = false;
    
    cocos2d::Vec2 previousTouchPoint;
    
    cocos2d::Animate *heroFlyLeft;
    cocos2d::Animate *heroFlyRight;
    cocos2d::Animate *heroFlyUp;
    cocos2d::Animate *heroFlyDown;
    cocos2d::Animate *heroEat;
    cocos2d::Animate *heroCry;
    cocos2d::Animate *heroLaugh;
    
    bool isPunished;

    float MaxWidth;
    float MinWidth;
    float MaxHeight;
    float MinHeight;
};

#endif /* Hero_h */

//
//  Capsule.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/20.
//
//

#ifndef Capsule_h
#define Capsule_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"
#include "Hero.h"

enum CapsuleStatus {
    CAwait = 0,
    CRunning,
    CAppear
};

class Capsule: public cocos2d::Sprite {
public:
    Capsule(){};
    ~Capsule(){};
    
    CREATE_FUNC(Capsule);
    static Capsule *CreateSpriteWithFrame(const char *name);
    void InitCapsule();
    
    void CrashEdge1();
    void CrashEdge2();
    void CrashEdge3();
    void CrashEdge4();
    
    void InitSpeed();
    void FaceToHero();
    void CaptureHero();
    bool IsAlive() const {return available;};
    void Dead(){this->available = false;};
    void SetStatus(CapsuleStatus status){this->status = status;};
    CapsuleStatus GetStatus() const {return status;};
    
    void SetHeroPosition(cocos2d::Vec2 Position){this->heroPosition = Position;};
    cocos2d::Vec2 GetHeroPosition() const{return this->heroPosition;};
    void RequestHeroPosition(Hero* hero);
    
    void SetBaseVelocity(float value){this->baseVelocity = value;};
    float GetBaseVelocity() const{return this->baseVelocity;};
    void SetVelocity(cocos2d::Vec2 v){this->velocity = v;};
    cocos2d::Vec2 GetVelocity() const{return this->velocity;};
    
    void AppearAction();
    void FlyToHero();
    void Clocker();
    
    void SetLifeCycle(float life){lifeCycle = life;};
private:
    bool available;
    cocos2d::Vec2 heroPosition;
    cocos2d::Vec2 velocity;
    float baseVelocity;
    float lifeCycle;
    
    CapsuleStatus status;
    
    float offSetX;
    float offSetY;
};

#endif /* Capsule_h */

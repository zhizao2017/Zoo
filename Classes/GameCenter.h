//
//  GameCenter.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#ifndef GameCenter_h
#define GameCenter_h

#include <stdio.h>
#include "cocos2d.h"
#include "SlideDirection.h"
#include "Hero.h"
#include "Capsule.h"
#include "Transistor.h"
#include "Define.h"

enum contactType {
    CapsuleEdge1 = 0,
    Edge1Capsule,
    CapsuleEdge2,
    Edge2Capsule,
    CapsuleEdge3,
    Edge3Capsule,
    CapsuleEdge4,
    Edge4Capsule,
    CapsuleHero,
    HeroCapsule,
    TransistorEdge1,
    Edge1Transistor,
    TransistorEdge2,
    Edge2Transistor,
    TransistorEdge3,
    Edge3Transistor,
    TransistorEdge4,
    Edge4Transistor,
    TransistorHero,
    HeroTransistor,
    HeroEdge,
    EdgeHero,
    NoneContact
};

class GameCenter {
public:
    GameCenter();
    ~GameCenter(){};
    
    void SetHero(Hero *hero){this->hero = hero;};
    Hero *GetHero() const{return this->hero;};
    
    bool IsGameOver(){return true;};
    
    bool IsACapsule(int tag){return this->capsuleSet->find(tag) != this->capsuleSet->end();};
    bool IsATransistor(int tag){return this->transistorSet->find(tag) != this->transistorSet->end();};
    bool IsAEdge(int tag){return (tag == kEdge1)||(tag == kEdge2)||(tag == kEdge3)||(tag == kEdge4);};
    bool IsHero(int tag){return tag == kHero;};
    
    void AddCapsule(Capsule *capsule){ capsule->setTag(capsuleIndex);this->capsuleSet->insert(capsuleIndex++, capsule);};
    Capsule *GetCapsule(int tag){return capsuleSet->at(tag);};
    
    void AddTransistor(Transistor *transistor){transistor->setTag(transistorIndex);this->transistorSet->insert(transistorIndex++, transistor);};
    Transistor *GetTransistor(int tag){return transistorSet->at(tag);};
    cocos2d::Map<int, Transistor*> *GetTransistors(){return transistorSet;};
    
    void DoContact(cocos2d::PhysicsContact &contact);
    contactType SniffContactType(int tagA, int tagB);
    
    void updateHeroPosition();
    
    void ResetTime(){remainedTime = 120;};
    
    void DecreaseTime(float delta);
    void IncreaseTime(float delta){remainedTime += delta;};
    
    void SetTarget(transistorType type){this->heroTarget = type;};
    transistorType GetTarget() const{return this->heroTarget;};
    
    static transistorType GenerateRandomTransistorType();
    void TransistorPunish();
    void TransistorBonus();
    
    bool IsFinalScene(){return isFinalScene;};
    
    float GetRemainedTime(){return remainedTime;};
    
    void IncreaseScore(float score){playerScore += score;};
    float GetScore(){return playerScore;};
    
    void ClearALLTransistor(){transistorSet->clear();transistorIndex=20000;};
    void ClearALLCapsule(){capsuleSet->clear();capsuleIndex=10000;};
private:
    
    Hero *hero;
    int capsuleIndex;
    int transistorIndex;
    int atenTransistor;
    float remainedTime;
    float widthRate;
    float heightRate;
    
    float playerScore;
    
    void EatTransistor();
    transistorType heroTarget;
    bool isFinalScene;
    
    void PerformHeroEatTransistorAnimation(Transistor *transistor, bool isBonus);
    void PerformCapsuleBeatHeroAnimation(Capsule *capsule);
    
    cocos2d::Map<int, Capsule *> *capsuleSet;
    cocos2d::Map<int, Transistor *> *transistorSet;
};

#endif /* GameCenter_h */

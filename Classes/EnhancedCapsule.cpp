//
//  EnhancedCapsule.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/31.
//
//

#include "EnhancedCapsule.h"

EnhancedCapsule *EnhancedCapsule::CreateSpriteWithFrame(const char* name) {
    EnhancedCapsule *enhancedCapsule = EnhancedCapsule::create();
    if (enhancedCapsule) {
        enhancedCapsule->setTexture(name);
        enhancedCapsule->InitCapsule();
        enhancedCapsule->InitEnhancdCapsule();
        return enhancedCapsule;
    }
    return NULL;
}

void EnhancedCapsule::InitEnhancdCapsule() {
    SetBaseVelocity(300);
    this->setScale(0.75);
    this->setVisible(false);
    this->schedule(schedule_selector(EnhancedCapsule::update), 1.0/60);
    this->schedule(schedule_selector(EnhancedCapsule::LiveMethod), 1.0);
    metric = 3;
    
    lifeCycle = 2;
}

void EnhancedCapsule::LiveMethod(float delta) {
    if (GetStatus() == CRunning) {
        lifeCycle -= delta;
        if (lifeCycle <= 0){
            this->Dead();
            this->setVisible(false);
            this->removeFromParent();
        }
    }
}

void EnhancedCapsule::update(float delta) {
    metric -= delta;
    if (metric <= 0 && GetStatus() == CAwait) {
        SetStatus(CAppear);
        AppearAction();
        this->setPosition(appearPosition);
    } else if (GetStatus() == CRunning) {
        FaceToHero();
        CaptureHero();
    } else {
        //pass
    }
}

void EnhancedCapsule::SniffAppearPosition(cocos2d::Map<int, Transistor*> *transistorSet) {
    cocos2d::Vec2 heroPosition = GetHeroPosition();
    cocos2d::Map<int, Transistor *>::iterator pos;
    float min = 4000;
    for (pos = transistorSet->begin(); pos != transistorSet->end(); pos++) {
        if (pos->second != NULL) {
            Transistor *transistor = pos->second;
            if (transistor->IsAlive()) {
                cocos2d::Vec2 point = transistor->getPosition();
                cocos2d::Vec2 vector = point - heroPosition;
                float z = sqrt(vector.x * vector.x + vector.y * vector.y);
                float angle;
                float randomNum = cocos2d::rand_0_1();
                if(randomNum >= 0 && randomNum < 0.25) {
                    angle = cocos2d::random(0, 90);
                } else if (randomNum >= 0.25 && randomNum < 0.5) {
                    angle = cocos2d::random(90, 180);
                } else if (randomNum >= 0.5 && randomNum < 0.75) {
                    angle = cocos2d::random(-180, -90);
                } else {
                    angle = cocos2d::random(-90, 0);
                }
                float velocityX = 100 * sin(CC_DEGREES_TO_RADIANS(angle));
                float velocityY = 100 * cos(CC_DEGREES_TO_RADIANS(angle));
            
                if (z < min) {
                    float vx = point.x + velocityX;
                    float vy = point.y + velocityY;
                    appearPosition = cocos2d::Vec2(vx, vy);
                }
            }
        }
    }
}
//
//  NormalCapsule.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/30.
//
//

#include "NormalCapsule.h"

NormalCapsule *NormalCapsule::CreateSpriteWithFrame(const char* name) {
    NormalCapsule *normalCapsule = NormalCapsule::create();
    if (normalCapsule) {
        normalCapsule->setTexture(name);
        normalCapsule->InitCapsule();
        normalCapsule->InitNormalCapsule();
        return normalCapsule;
    }
    return NULL;
}

void NormalCapsule::InitNormalCapsule() {
    SetBaseVelocity(200);
    this->setScale(0.75);
    this->setVisible(false);
    this->schedule(schedule_selector(NormalCapsule::update), 1.0/60);
    this->schedule(schedule_selector(NormalCapsule::LiveMethod), 1.0);
    metric = 3;
    
    lifeCycle = 10;
}

void NormalCapsule::LiveMethod(float delta) {
    if (GetStatus() == CRunning) {
        lifeCycle -= delta;
        if (lifeCycle <= 0){
            this->Dead();
            this->setVisible(false);
            this->removeFromParent();
        }
        
    }
}

void NormalCapsule::update(float delta) {
    metric -= delta;
    if (metric <= 0 && GetStatus() == CAwait) {
        AppearAction();
        SetStatus(CAppear);
    } else if (GetStatus() == CRunning) {
        //HitHero();
    } else {
        //pass
    }

}
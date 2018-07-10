//
//  Capsule.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/20.
//
//

#include "Capsule.h"

Capsule *Capsule::CreateSpriteWithFrame(const char* name) {
    Capsule *capsule = Capsule::create();
    if (capsule) {
        capsule->setTexture(name);
        capsule->InitCapsule();
        return capsule;
    }
    return NULL;
}

void Capsule::InitCapsule() {
    available = true;
    this->setScale(0.75);
    
    auto body = cocos2d::PhysicsBody::createBox(this->getContentSize());
    body->setCategoryBitmask(0x04);
    body->setContactTestBitmask(0x07);
    body->setCollisionBitmask(0);
    this->setPhysicsBody(body);
    
    this->velocity = cocos2d::Vec2(0, 0);
    this->baseVelocity = 0;
    this->lifeCycle = 3;
    SetStatus(CAwait);
}

void Capsule::FaceToHero() {
    cocos2d::Vec2 vector = heroPosition - this->getPosition();
    float angle = vector.getAngle();
    this->setRotation(180 - CC_RADIANS_TO_DEGREES(angle));
}

void Capsule::CaptureHero() {
    cocos2d::Vec2 vector = heroPosition - this->getPosition();
    
    float z = sqrt(vector.x * vector.x + vector.y * vector.y);
    float rate = baseVelocity / z;
    this->velocity = cocos2d::Vec2(vector.x * rate, vector.y * rate);
    this->getPhysicsBody()->setVelocity(this->velocity);
}

void Capsule::RequestHeroPosition(Hero* hero) {
    this->heroPosition = hero->getPosition();
}

void Capsule::AppearAction() {
    setVisible(true);
    Dead();
    this->runAction(cocos2d::Sequence::create(cocos2d::Blink::create(3, 12), cocos2d::CallFunc::create(CC_CALLBACK_0(Capsule::FlyToHero, this)), NULL));
}

void Capsule::FlyToHero() {
    stopAllActions();
    available = true;
    SetStatus(CRunning);
    cocos2d::Vec2 vector = heroPosition - this->getPosition();
    
    float angle = vector.getAngle();
    this->setRotation(180 - CC_RADIANS_TO_DEGREES(angle));
    
    float z = sqrt(vector.x * vector.x + vector.y * vector.y);
    float rate = 300 / z;
    cocos2d::Vec2 velocity = cocos2d::Vec2(vector.x * rate, vector.y * rate);
    this->getPhysicsBody()->setVelocity(velocity);
}
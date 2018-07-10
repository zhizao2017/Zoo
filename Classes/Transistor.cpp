//
//  Transistor.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/20.
//
//

#include "Transistor.h"

Transistor *Transistor::CreateTransistorSprite() {
    Transistor *transistor = Transistor::create();
    if (transistor) {
        transistor->InitTransistorSprite();
        return transistor;
    }
    return NULL;
}

void Transistor::InitTransistorSprite() {
    type = cocos2d::rand_0_1() < 0.5 ? TZero:TOne;
    this->transistor = cocos2d::Sprite::create();
    this->transistor->setPosition(this->getPosition());
    this->transistor->setScale(0.75);
    addChild(this->transistor);
    if (type == TZero) {
        this->transistor->setTexture(rTRANSISTORZERO);
    } else {
        this->transistor->setTexture(rTRANSISTORONE);
    }
    available = true;
    edible = false;
    isInTarget = false;
    
    auto body = cocos2d::PhysicsBody::createBox(this->transistor->getContentSize());
    body->setCategoryBitmask(0x04);
    body->setContactTestBitmask(0x07);
    body->setCollisionBitmask(0);
    this->setPhysicsBody(body);
    
    this->schedule(schedule_selector(Transistor::liveMethod), 1.0f);
    this->schedule(schedule_selector(Transistor::targetTips), 1.0f/60);
#warning modify font
    this->bounusPunishLabel = cocos2d::Label::create();
    
    this->baseVelocity = 200;
    this->lifeCycle = 5;
    InitSpeed();
    
    AppearAction();
    this->bounusPunishLabel = cocos2d::Label::createWithSystemFont("", "AppleGothic", 24);
    this->bounusPunishLabel->setVisible(false);
    this->addChild(this->bounusPunishLabel);
}

void Transistor::AppearAction() {
    this->transistor->runAction(cocos2d::Sequence::create(cocos2d::Blink::create(0.5, 2), cocos2d::CallFunc::create(CC_CALLBACK_0(Transistor::Activity, this)), NULL));
}

void Transistor::PerformBounsAnimation() {
    this->transistor->setVisible(false);
    this->bounusPunishLabel->setVisible(true);
    this->bounusPunishLabel->setString("+ 2S");
    this->bounusPunishLabel->setColor(cocos2d::Color3B(66, 213, 81));
    this->setPosition(this->getPosition());
    this->bounusPunishLabel->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.4f, 2), cocos2d::ScaleTo::create(0.4f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(Transistor::BounsAnimationEnd, this)), NULL));
}

void Transistor::PerformPunishAnimation() {
    this->transistor->setVisible(false);
#warning add Animation
    this->bounusPunishLabel->setVisible(true);
    this->bounusPunishLabel->setString("- 5S");
    this->bounusPunishLabel->setColor(cocos2d::Color3B(251, 33, 37));
    this->setPosition(this->getPosition());
    this->bounusPunishLabel->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.4f, 2), cocos2d::ScaleTo::create(0.4f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(Transistor::PunishAnimationEnd, this)), NULL));
}

void Transistor::PunishAnimationEnd() {
    this->Dead();
    this->setVisible(false);
    this->removeFromParent();
}

void Transistor::BounsAnimationEnd() {
    this->Dead();
    this->setVisible(false);
    this->removeFromParent();
}

void Transistor::TargetAnimationEnd() {
    isInTarget = false;
}

void Transistor::liveMethod(float delta) {
    if (edible) {
        this->lifeCycle -= delta;
        if (this->lifeCycle <= 0) {
            this->Dead();
            this->setVisible(false);
            this->removeFromParent();
        }
    }
}

void Transistor::targetTips(float delta) {
    if (target == type && isInTarget == false) {
        this->transistor->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.4f, 0.65), cocos2d::ScaleTo::create(0.4f, 0.75), cocos2d::CallFunc::create(CC_CALLBACK_0(Transistor::TargetAnimationEnd, this)), NULL));
        isInTarget = true;
    }
}

void Transistor::InitSpeed() {
    float randomAngle = cocos2d::random(-90, 90);
    float velocityX = baseVelocity * sin(CC_DEGREES_TO_RADIANS(randomAngle));
    float velocityY = baseVelocity * cos(CC_DEGREES_TO_RADIANS(randomAngle));
    if (velocityY > 0) {
        velocityY = 0 - velocityY;
    }
    this->velocity = cocos2d::Vec2(velocityX, velocityY);
}

void Transistor::CrashEdge1() {
    float randomAngle = cocos2d::random(0, 90);
    float velocityX = baseVelocity * sin(CC_DEGREES_TO_RADIANS(randomAngle));
    float velocityY = baseVelocity * cos(CC_DEGREES_TO_RADIANS(randomAngle));
    this->velocity.x = velocityX;
    if (cocos2d::random(0, 1) == 1) {
        this->velocity.y = 0 - velocityY;
    } else {
        this->velocity.y = velocityY;
    }
    
    this->getPhysicsBody()->setVelocity(this->velocity);
}

void Transistor::CrashEdge2() {
    float randomAngle = cocos2d::random(0, 90);
    float velocityX = baseVelocity * sin(CC_DEGREES_TO_RADIANS(randomAngle));
    float velocityY = baseVelocity * cos(CC_DEGREES_TO_RADIANS(randomAngle));
    this->velocity.y = 0 - velocityY;
    if (cocos2d::random(0, 1) == 1) {
        this->velocity.x = 0 - velocityX;
    } else {
        this->velocity.x = velocityX;
    }
    
    this->getPhysicsBody()->setVelocity(this->velocity);
}

void Transistor::CrashEdge3() {
    float randomAngle = cocos2d::random(0, 90);
    float velocityX = baseVelocity * sin(CC_DEGREES_TO_RADIANS(randomAngle));
    float velocityY = baseVelocity * cos(CC_DEGREES_TO_RADIANS(randomAngle));
    this->velocity.x = 0 - velocityX;
    if (cocos2d::random(0, 1) == 1) {
        this->velocity.y = 0 - velocityY;
    } else {
        this->velocity.y = velocityY;
    }
    
    this->getPhysicsBody()->setVelocity(this->velocity);
}

void Transistor::CrashEdge4() {
    float randomAngle = cocos2d::random(0, 90);
    float velocityX = baseVelocity * sin(CC_DEGREES_TO_RADIANS(randomAngle));
    float velocityY = baseVelocity * cos(CC_DEGREES_TO_RADIANS(randomAngle));
    this->velocity.y = velocityY;
    if (cocos2d::random(0, 1) == 1) {
        this->velocity.x = 0 - velocityX;
    } else {
        this->velocity.x = velocityX;
    }
    
    this->getPhysicsBody()->setVelocity(this->velocity);
}
//
//  Hero.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#include "Hero.h"

Hero *Hero::CreateSpriteWithFrame(const char *name) {
    Hero *hero = Hero::create();
    if (hero) {
        hero->InitHero();
        hero->InitHeroAnimation();
        return hero;
    }
    return NULL;
}

void Hero::InitHero() {
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    this->setTexture(rHERO);
    this->setTag(kHero);
    this->setScale(0.75);
    this->SetStatus(HAwait);
    
    isPunished = false;
    
    physicsBody = cocos2d::PhysicsBody::create();
    auto physicsShape = cocos2d::PhysicsShapeCircle::create(this->getContentSize().width/2);
    physicsBody->addShape(physicsShape);
    physicsBody->setCategoryBitmask(0x04);
    physicsBody->setContactTestBitmask(0x07);
    physicsBody->setCollisionBitmask(0);

    this->setPhysicsBody(physicsBody);
    
    this->schedule(schedule_selector(Hero::update), 1.0/60);
    
    MinWidth = this->getContentSize().width*0.75/2;
    MaxWidth = size.width - this->getContentSize().width*0.75/2;
    MinHeight = this->getContentSize().height*0.75/2;
    MaxHeight = size.height - this->getContentSize().height*0.75/2;
}

void Hero::InitHeroAnimation() {
    this->heroCry = cocos2d::Animate::create(CreateAnimation("Animation/cry/hero_cry.plist", "hero_cry_", 8, 1.0/8, false));
    this->heroCry->retain();
    this->heroCry->setTag(aCry);
    this->heroEat = cocos2d::Animate::create(CreateAnimation("Animation/eat/hero_eat.plist", "hero_eat_", 32, 2.0/32, false));
    this->heroEat->retain();
    this->heroEat->setTag(aEat);
    /*this->heroFlyDown = cocos2d::Animate::create(CreateAnimation("Animation/down/hero_fly_down.plist", "hero_fly_down_", 8, 1.0/8, false));
    this->heroFlyDown->retain();
    this->heroFlyDown->setTag(aFlyDown);
    this->heroFlyUp = cocos2d::Animate::create(CreateAnimation("Animation/up/hero_fly_up.plist", "hero_fly_up_", 8, 1.0/8, false));
    this->heroFlyUp->retain();
    this->heroFlyUp->setTag(aFlyUp);
    this->heroFlyLeft = cocos2d::Animate::create(CreateAnimation("Animation/left/hero_fly_left.plist", "hero_fly_left_", 8, 1.0/8, false));
    this->heroFlyLeft->retain();
    this->heroFlyLeft->setTag(aFlyLeft);*/
    this->heroFlyRight = cocos2d::Animate::create(CreateAnimation("Animation/right/hero_fly_right.plist", "hero_fly_right_", 8, 1.0/8, false));
    this->heroFlyRight->retain();
    this->heroFlyRight->setTag(aFlyRight);
    this->heroLaugh = cocos2d::Animate::create(CreateAnimation("Animation/laugh/hero_laugh.plist", "hero_laugh_", 8, 1.0/8, false));
    this->heroLaugh->retain();
    this->heroLaugh->setTag(aLaugh);
}

cocos2d::Animation *Hero::CreateAnimation(const char *resourcePath, const char *prefix, int frameCount, float delay, bool isLoops) {
    cocos2d::SpriteFrameCache *cache = cocos2d::SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(resourcePath);
    
    cocos2d::Vector<cocos2d::SpriteFrame *> spriteFrames;
    for (int i = 1; i <= frameCount; i++) {
        std::stringstream ss;
        ss << prefix << i << ".png";
        std::string name = ss.str();
        cocos2d::SpriteFrame *frame = cache->getSpriteFrameByName(name);
        spriteFrames.pushBack(frame);
    }
    
    cocos2d::Animation *animation = cocos2d::Animation::createWithSpriteFrames(spriteFrames, delay);
    if (isLoops) {
        animation->setLoops(-1);
    } else {
        animation->setLoops(1);
    }
        
    return animation;
}

void Hero::MoveTo(cocos2d::Vec2 currentPoint) {
    cocos2d::Vec2 vector = currentPoint - this->previousTouchPoint;
    
    if (currentPoint.x > this->previousTouchPoint.x) {
        this->setFlippedX(false);
    } else {
        this->setFlippedX(true);
    }
    
    float currentX = this->getPositionX();
    float currentY = this->getPositionY();
    
    currentX = currentX + vector.x;
    currentY = currentY + vector.y;
    
    if (currentX < MinWidth) {
        currentX = MinWidth;
    } else if (currentX > MaxWidth) {
        currentX = MaxWidth;
    }
    if (currentY > MaxHeight) {
        currentY = MaxHeight;
    } else if (currentY < MinHeight) {
        currentY = MinHeight;
    }
    this->setPosition(cocos2d::Vec2(currentX, currentY));
    if (status == HAwait){
        this->SetStatus(HMoving);
        this->PerformAction(heroFlyRight, false);
    }
}

void Hero::CrashEdge() {
    DoLaughing();
    SetStatus(HLaughing);
}

void Hero::ResetStatus() {
    this->status = HAwait;
    if(isPunished) {
        isPunished = false;
    };
    this->setTexture(rHERO);
    this->setFlippedX(true);
    /*if (isDelete == true) {
        isDelete = false;
        //this->getPhysicsBody()->setPositionOffset(cocos2d::Vec2(0, 0));
    }*/
}

void Hero::DoCrying() {
    stopAllActions();
    BePunished();
    
#warning modify
    /*Test
    isDelete = true;
    
    //this->getPhysicsBody()->setPositionOffset(cocos2d::Vec2(this->getContentSize().width*2/3, 0));
    */
    
    this->PerformAction(heroCry, false);
    SetStatus(HCrying);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("2.wav");
}

void Hero::DoEating(bool isBouns) {
    stopAllActions();
    this->PerformAction(heroEat, isBouns);
    SetStatus(HEating);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("1.wav");
}

void Hero::DoLaughing() {
    stopAllActions();
    this->PerformAction(heroLaugh, false);
    SetStatus(HLaughing);
}

void Hero::update(float delta) {}


void Hero::PerformAction(cocos2d::Animate *action, bool isBouns) {
    if (isBouns) {
        this->runAction(cocos2d::Sequence::create(action, heroLaugh, cocos2d::CallFunc::create(CC_CALLBACK_0(Hero::ResetStatus, this)), NULL));
    } else {
        this->runAction(cocos2d::Sequence::create(action, cocos2d::CallFunc::create(CC_CALLBACK_0(Hero::ResetStatus, this)), NULL));
    }
}
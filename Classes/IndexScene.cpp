//
//  IndexScene.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#include "IndexScene.h"

cocos2d::Scene* IndexScene::createScene() {
    auto scene = cocos2d::Scene::createWithPhysics();
    cocos2d::Vect gravity = cocos2d::Vect(0, 0);
    scene->getPhysicsWorld()->setGravity(gravity);
    //scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = IndexScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool IndexScene::init() {
    if ( !Layer::init()) {
        return false;
    }
    
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    cocos2d::Sprite *bg = cocos2d::Sprite::create(rMENUBACK);
    bg->setPosition(cocos2d::Vec2(size.width/2, size.height/2));
    addChild(bg);
    
    band = cocos2d::Label::createWithSystemFont("l/0", "AppleGothic", 200);
    band->setPosition(cocos2d::Vec2(size.width/2, size.height*3/4));
    band->setColor(cocos2d::Color3B(101, 108, 124));
    addChild(band);
    
    cocos2d::MenuItemFont::setFontSize(43);
    
    cocos2d::MenuItemFont *item1 = cocos2d::MenuItemFont::create("START", CC_CALLBACK_1(IndexScene::menuItemStartGameCallback, this));
    cocos2d::MenuItemFont *item2 = cocos2d::MenuItemFont::create("CREDITS", CC_CALLBACK_1(IndexScene::menuItemCreditsCallback, this));
    cocos2d::Menu *mn = cocos2d::Menu::create(item1, item2, NULL);
    mn->alignItemsVertically();
    this->addChild(mn);

    cocos2d::EventListenerPhysicsContact *contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(IndexScene::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(IndexScene::onContactSeperate, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->schedule(schedule_selector(IndexScene::MainLoop), 1.0/60);
    
    isMove = false;
    isHold = false;
    InitHeroAnimation();
    
    CreateTutorialAnimation();
    DoTutorialAnimation();
    
    return true;
}

void IndexScene::menuItemCreditsCallback(cocos2d::Ref *pSender) {

}

void IndexScene::menuItemStartGameCallback(cocos2d::Ref *pSender) {
    auto gameScene = GameScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(gameScene);
}

void IndexScene::CreateTutorialAnimation() {
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    hero = cocos2d::Sprite::create(rHERO);
    hero->setScale(0.75);
    hero->setPosition(cocos2d::Vec2(10+hero->getContentSize().width/2, 100+hero->getContentSize().height/2));
    auto body = cocos2d::PhysicsBody::createCircle(this->hero->getContentSize().width/2);
    body->setCategoryBitmask(0x04);
    body->setContactTestBitmask(0x07);
    body->setCollisionBitmask(0);
    this->hero->setPhysicsBody(body);
    addChild(hero);
    
    obj = cocos2d::Sprite::create(rTRANSISTORONE);
    obj->setScale(0.75);
    obj->setPosition(cocos2d::Vec2(size.width-10-obj->getContentSize().width/2, 100+hero->getContentSize().height/2));
    body = cocos2d::PhysicsBody::createBox(this->obj->getContentSize());
    body->setCategoryBitmask(0x04);
    body->setContactTestBitmask(0x07);
    body->setCollisionBitmask(0);
    this->obj->setPhysicsBody(body);
    addChild(obj);
    
    bonusLabel = cocos2d::Label::createWithSystemFont("", "AppleGothic", 24);
    bonusLabel->setPosition(cocos2d::Vec2(cocos2d::Vec2(size.width-10-obj->getContentSize().width/2, 100+hero->getContentSize().height/2)));
    bonusLabel->setVisible(false);
    addChild(bonusLabel);

    tutorialLeftPoint = cocos2d::Vec2(10+hero->getContentSize().width/2, 100+hero->getContentSize().height/2);
    tutorialRightPoint = cocos2d::Vec2(size.width-10-obj->getContentSize().width/2, 100+hero->getContentSize().height/2);
    tutorialMidPoint = cocos2d::Vec2(size.width/2, 100+hero->getContentSize().height/2);
}

void IndexScene::MainLoop(float delta) {
    if (!isMove) {
        this->hero->setFlippedX(false);
        this->hero->runAction(heroFly);
        isMove = true;
    }
}

void IndexScene::DoTutorialAnimation() {
    currentEpisode = cocos2d::random(0, 2);
    hero->setVisible(true);
    if (currentEpisode == 0) { //Beat Hero
        this->hero->setPosition(tutorialMidPoint);
        this->hero->runAction(cocos2d::MoveTo::create(3, tutorialRightPoint));
        
        this->obj->setTexture(rCAPSULE);
        obj->setVisible(true);
        this->obj->setPosition(tutorialLeftPoint);
        configPoint.controlPoint_1 = cocos2d::Vec2(200, 0);
        configPoint.controlPoint_1 = cocos2d::Vec2(400, 300);
        configPoint.endPosition = tutorialRightPoint;
        this->obj->runAction(cocos2d::BezierTo::create(3, configPoint));
    } else if (currentEpisode == 1) {//bonus
        this->hero->setPosition(tutorialLeftPoint);
        this->hero->runAction(cocos2d::MoveTo::create(3, tutorialMidPoint));
        
        this->obj->setTexture(rTRANSISTORONE);
        obj->setVisible(true);
        this->obj->setPosition(tutorialMidPoint);
        this->obj->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.4f, 0.8), cocos2d::ScaleTo::create(0.4f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(IndexScene::ScaleAnimationEnd, this)),NULL));
    } else if (currentEpisode == 2) {//punish
        this->hero->setPosition(tutorialLeftPoint);
        this->hero->runAction(cocos2d::MoveTo::create(3, tutorialMidPoint));
        
        this->obj->setTexture(rTRANSISTORONE);
        this->obj->setPosition(tutorialMidPoint);
        obj->setVisible(true);
    }
}

void IndexScene::InitHeroAnimation() {
    this->heroCry = cocos2d::Animate::create(CreateAnimation("Animation/cry/hero_cry.plist", "hero_cry_", 8, 1.0/8, false));
    this->heroCry->retain();
    this->heroEat = cocos2d::Animate::create(CreateAnimation("Animation/eat/hero_eat.plist", "hero_eat_", 32, 2.0/32, false));
    this->heroEat->retain();
    this->heroFly = cocos2d::Animate::create(CreateAnimation("Animation/right/hero_fly_right.plist", "hero_fly_right_", 8, 1.0/8, true));
    this->heroFly->retain();
    this->heroLaugh = cocos2d::Animate::create(CreateAnimation("Animation/laugh/hero_laugh.plist", "hero_laugh_", 8, 1.0/8, false));
    this->heroLaugh->retain();
}

cocos2d::Animation *IndexScene::CreateAnimation(const char *resourcePath, const char *prefix, int frameCount, float delay, bool isLoops) {
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

void IndexScene::ScaleAnimationEnd() {
    if (currentEpisode == 1) {
        this->obj->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.4f, 0.8), cocos2d::ScaleTo::create(0.4f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(IndexScene::ScaleAnimationEnd, this)), NULL));
    }
}

void IndexScene::BonusAnimationEnd() {
    this->bonusLabel->setVisible(false);
}

void IndexScene::ResetStatus() {
    isMove = false;
    hero->stopAllActions();
    obj->stopAllActions();
    bonusLabel->stopAllActions();
    bonusLabel->setVisible(false);
    DoTutorialAnimation();
}

bool IndexScene::onContactBegin(cocos2d::PhysicsContact &contact) {
    obj->setVisible(false);
    if (currentEpisode == 0) {
        this->hero->stopAllActions();
        this->hero->runAction(cocos2d::Sequence::create(heroCry, cocos2d::CallFunc::create(CC_CALLBACK_0(IndexScene::ResetStatus, this)), NULL));
    } else if (currentEpisode == 1) {
        this->hero->stopAllActions();
        this->hero->runAction(cocos2d::Sequence::create(heroEat, heroLaugh, cocos2d::CallFunc::create(CC_CALLBACK_0(IndexScene::ResetStatus, this)), NULL));
        
        this->bonusLabel->setPosition(tutorialMidPoint);
        this->bonusLabel->setVisible(true);
        this->bonusLabel->setString("+ 2S");
        this->bonusLabel->setColor(cocos2d::Color3B(cocos2d::Color3B(66, 213, 81)));
        this->bonusLabel->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.4f, 2), cocos2d::ScaleTo::create(0.4f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(IndexScene::ScaleAnimationEnd, this)),NULL));
    } else if (currentEpisode == 2) {
        this->hero->stopAllActions();
        this->hero->runAction(cocos2d::Sequence::create(heroEat, cocos2d::CallFunc::create(CC_CALLBACK_0(IndexScene::ResetStatus, this)), NULL));
        
        this->bonusLabel->setPosition(tutorialMidPoint);
        this->bonusLabel->setVisible(true);
        this->bonusLabel->setString("- 5S");
        this->bonusLabel->setColor(cocos2d::Color3B(cocos2d::Color3B(251, 33, 37)));
        this->bonusLabel->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.4f, 2), cocos2d::ScaleTo::create(0.4f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(IndexScene::ScaleAnimationEnd, this)), NULL));
    }
    return true;
}

void IndexScene::onContactSeperate(cocos2d::PhysicsContact &contact) {
    
}
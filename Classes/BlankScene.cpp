//
//  BlankScene.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/25.
//
//

#include "BlankScene.h"

cocos2d::Scene* BlankScene::createScene() {
    auto scene = cocos2d::Scene::create();
    
    auto layer = BlankScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool BlankScene::init() {
    if ( !Layer::init()) {
        return false;
    }
    
    auto touchEventListener = cocos2d::EventListenerTouchOneByOne::create();
    touchEventListener->onTouchBegan = CC_CALLBACK_2(BlankScene::onTouchBegan, this);
    touchEventListener->setSwallowTouches(true);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(touchEventListener, -127);
    
    return true;
}

bool BlankScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    return true;
}
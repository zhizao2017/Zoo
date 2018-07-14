//
//  PauseButton.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/24.
//
//

#include "PauseButton.h"
#include "cocos2d.h"

USING_NS_CC;

PauseButton *PauseButton::CreateSpriteWithFrame() {
    PauseButton *pauseButton = PauseButton::create();
    if (pauseButton) {
        pauseButton->InitPauseButton();
        return pauseButton;
    }
    return NULL;
}

void PauseButton::InitPauseButton() {
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    bool is_iP_X = false;
    
    if (Director::getInstance()->getVisibleSize().height == 2436) {
        is_iP_X = true;
    }
    
    this->setTexture(rPause);
    if (is_iP_X) {
        this->setPosition(size.width - this->getContentSize().width/2 - 5, size.height - this->getContentSize().height/2 - 5 - 85);
    } else {
        this->setPosition(size.width - this->getContentSize().width/2 - 5, size.height - this->getContentSize().height/2 - 5);
    }
        
    cocos2d::Size s = this->getContentSize();
    if (is_iP_X) {
        this->buttonRect = cocos2d::Rect(size.width - 10 - this->getContentSize().width, size.height - 10 - this->getContentSize().height, size.width - 10, s.height - 10 - 85);
    } else {
        this->buttonRect = cocos2d::Rect(size.width - 10 - this->getContentSize().width, size.height - 10 - this->getContentSize().height, size.width - 10, s.height - 10);
    }

    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PauseButton::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool PauseButton::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    if (this->buttonRect.containsPoint(pTouch->getLocation())) {
        cocos2d::RenderTexture *renderTexture = cocos2d::RenderTexture::create(size.width, size.height);
        renderTexture->begin();
        this->getParent()->visit();
        renderTexture->end();
        
        auto inGameMenu = InGameMenu::createScene();
        cocos2d::Director::getInstance()->pushScene(inGameMenu);
    }
        return true;
}

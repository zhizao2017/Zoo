//
//  Bubble.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/3/5.
//
//

#include "Bubble.h"

Bubble *Bubble::CreateSpriteWithFrame(BubbleType type) {
    Bubble *bubble = Bubble::create();
    if (bubble) {
        bubble->InitBubble(type);
        return bubble;
    }
    return NULL;
}

void Bubble::InitBubble(BubbleType type) {
    if (type == BLeft) {
        this->setTexture(rLeftBubble);
    } else {
        this->setTexture(rRightBubble);
    }
    this->setScale(1.5);
    
    message = cocos2d::Label::create();
    message->setPosition(cocos2d::Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    message->setScale(1.25);
    message->setColor(cocos2d::Color3B(30, 32, 40));
    addChild(message);
    
    this->setVisible(false);
}
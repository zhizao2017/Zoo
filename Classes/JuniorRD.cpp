//
//  JuniorRD.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/30.
//
//

#include "JuniorRD.h"

JuniorRD *JuniorRD::CreateJuniorRDSprite() {
    JuniorRD *juniorRD = JuniorRD::create();
    if (juniorRD != NULL) {
        juniorRD->InitJuniorRDSprite();
        return juniorRD;
    }
    return NULL;
}

void JuniorRD::InitJuniorRDSprite() {
    this->setTexture(rJuniorRD);
    this->setScale(0.75);
    
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    float x = size.width/10*9 - 15;
    float y = this->getContentSize().height/2 + 5;
    this->setPosition(cocos2d::Vec2(x, y));
}
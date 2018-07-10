//
//  SeniorRD.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/30.
//
//

#include "SeniorRD.h"

SeniorRD *SeniorRD::CreateSeniorRDSprite() {
    SeniorRD *seniorRD = SeniorRD::create();
    if (seniorRD != NULL) {
        seniorRD->InitSeniorRDSprite();
        return seniorRD;
    }
    return NULL;
}

void SeniorRD::InitSeniorRDSprite() {
    this->setTexture(rSeniorRD);
    this->setScale(0.75);
    
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    float x = size.width / 10 + 15;
    float y = this->getContentSize().height / 2 + 5;
    this->setPosition(cocos2d::Vec2(x, y));
}
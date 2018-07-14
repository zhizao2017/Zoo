//
//  StatusBar.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/20.
//
//

#include "StatusBar.h"
#include "cocos2d.h"

USING_NS_CC;

StatusBar *StatusBar::CreateSpriteWithFrame() {
    StatusBar *statusBar = StatusBar::create();
    if (statusBar) {
        statusBar->InitStatusBar();
        return statusBar;
    }
    return NULL;
}

void StatusBar::InitStatusBar() {
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    bool is_iP_X = false;
    
    if (Director::getInstance()->getVisibleSize().height == 2436) {
        is_iP_X = true;
    }
    
    this->heroAvatar = cocos2d::Sprite::create(rAvatar);
    if (is_iP_X) {
        this->heroAvatar->setPosition(20 + this->heroAvatar->getContentSize().width*0.75/2, size.height - this->heroAvatar->getContentSize().height*0.75/2 - 20 - 44);
    } else {
        this->heroAvatar->setPosition(20 + this->heroAvatar->getContentSize().width*0.75/2, size.height - this->heroAvatar->getContentSize().height*0.75/2 - 20);
    }

    this->addChild(this->heroAvatar);
    
    cocos2d::Sprite *avatarFill = cocos2d::Sprite::create(rAvatarFill);
    this->progressTimer = cocos2d::ProgressTimer::create(avatarFill);
    this->progressTimer->setType(cocos2d::ProgressTimer::Type::BAR);
    this->progressTimer->setBarChangeRate(cocos2d::Vec2(0, 1));
    this->progressTimer->setMidpoint(cocos2d::Vec2(0, 0));
    if (is_iP_X) {
        this->progressTimer->setPosition(20 + this->heroAvatar->getContentSize().width*0.75/2, size.height - this->heroAvatar->getContentSize().height*0.75/2 - 20 - 44);
    } else {
        this->progressTimer->setPosition(20 + this->heroAvatar->getContentSize().width*0.75/2, size.height - this->heroAvatar->getContentSize().height*0.75/2 - 20);
    }

    this->addChild(this->progressTimer);
    
    this->objectiveLabel = cocos2d::Label::createWithSystemFont("Objective", "AppleGothic", 24);
    if (is_iP_X) {
        this->objectiveLabel->setPosition(cocos2d::Vec2(size.width/2, size.height - 50 - 80));
    } else {
        this->objectiveLabel->setPosition(cocos2d::Vec2(size.width/2, size.height - 50));
    }
    this->addChild(this->objectiveLabel);
    
    this->heroObjective = cocos2d::Sprite::create();
    if (is_iP_X) {
        this->heroObjective->setPosition(cocos2d::Vec2(size.width/2, size.height - 80 - 80));
    } else {
        this->heroObjective->setPosition(cocos2d::Vec2(size.width/2, size.height - 80));
    }
    this->addChild(heroObjective);
    
    this->highestScoreLabel = cocos2d::Label::createWithSystemFont("Best", "AppleGothic", 24);
    if (is_iP_X) {
        this->highestScoreLabel->setPosition(cocos2d::Vec2(size.width*3/4, size.height - 50 - 80));
    } else {
        this->highestScoreLabel->setPosition(cocos2d::Vec2(size.width*3/4, size.height - 50));
    }
    this->addChild(this->highestScoreLabel);
    
    this->highestScore = cocos2d::Label::createWithSystemFont(UserOptions::getInstance()->GetFormalHighestScore(), "AppleGothic", 24);
    if (is_iP_X) {
        this->highestScore->setPosition(cocos2d::Vec2(size.width*3/4, size.height - 80 - 80));
    } else {
        this->highestScore->setPosition(cocos2d::Vec2(size.width*3/4, size.height - 80));
    }
    this->addChild(this->highestScore);
    
    this->currentScoreLabel = cocos2d::Label::createWithSystemFont("Score", "AppleGothic", 24);
    if (is_iP_X) {
        this->currentScoreLabel->setPosition(cocos2d::Vec2(size.width/4, size.height - 50 - 80));
    } else {
        this->currentScoreLabel->setPosition(cocos2d::Vec2(size.width/4, size.height - 50));
    }
    this->addChild(this->currentScoreLabel);
    
    this->currentScore = cocos2d::Label::createWithSystemFont("", "AppleGothic", 24);
    if (is_iP_X) {
        this->currentScore->setPosition(cocos2d::Vec2(size.width/4, size.height - 80 - 80));
    } else {
        this->currentScore->setPosition(cocos2d::Vec2(size.width/4, size.height - 80));
    }
    this->addChild(this->currentScore);
    
    isGameOver = false;
    isNearlyEnd = false;
    
    remaindTime = 120;
    
    this->schedule(schedule_selector(StatusBar::update), 1.0f);
}

void StatusBar::NearlyAnimationEnd() {
    isNearlyEnd = false;
}

void StatusBar::SetScore(float score) {
    int minute = (int)score/60;
    int second = score - minute*60;
    std::stringstream ss;
    ss<<minute<<"'"<<second<<"\"";
    this->currentScore->setString(ss.str());
}

void StatusBar::update(float delta) {
    this->progressTimer->setPercentage(120 - remaindTime);
    if(progressTimer->getPercentage() >= 100) {
        isGameOver = true;
    } else if (progressTimer->getPercentage() >= 80 && progressTimer->getPercentage() < 100) {
        if (!isNearlyEnd) {
            this->progressTimer->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.2f, 0.75), cocos2d::ScaleTo::create(0.2f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(StatusBar::NearlyAnimationEnd, this)), NULL));
            
            this->heroAvatar->runAction(cocos2d::Sequence::create(cocos2d::ScaleTo::create(0.2f, 0.75), cocos2d::ScaleTo::create(0.2f, 1), cocos2d::CallFunc::create(CC_CALLBACK_0(StatusBar::NearlyAnimationEnd, this)), NULL));
            isNearlyEnd = true;
        }
    }
}

void StatusBar::SetHeroObjective(transistorType type) {
    if(type == TZero) {
        this->heroObjective->setTexture(rTRANSISTORZERO);
    } else {
        this->heroObjective->setTexture(rTRANSISTORONE);
    }
    this->heroObjective->setScale(0.75);
}

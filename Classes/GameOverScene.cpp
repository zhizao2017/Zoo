//
//  GameOverScene.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/27.
//
//

#include "GameOverScene.h"

GameOverScene* GameOverScene::createScene(float score) {
    GameOverScene *gover = new GameOverScene(score);
    if (gover && gover->init()) {
        gover->autorelease();
        return gover;
    }
    CC_SAFE_DELETE(gover);
    return nullptr;
}

GameOverScene::GameOverScene(float score) {
    this->score = score;
}

bool GameOverScene::init() {
    if ( !Scene::init()) {
        return false;
    }
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    cocos2d::Sprite *bg = cocos2d::Sprite::create(rMENUBACK);
    bg->setPosition(cocos2d::Vec2(size.width/2, size.height/2));
    addChild(bg);
    
    std::stringstream ss;
    ss<<UserOptions::getInstance()->TransferFormalHighestScore(this->score);
    scoreMessage = cocos2d::Label::createWithSystemFont(ss.str(), "AppleGothic", 128);
    scoreMessage->setPosition(size.width/2, size.height/2);
    addChild(scoreMessage);
    
    CreateCryAnimation();
    this->hero = cocos2d::Sprite::create(rHERO);
    this->hero->setPosition(cocos2d::Vec2(size.width/2, size.height*3/4));
    addChild(hero);
    hero->runAction(heroCry);
    
    cocos2d::MenuItemFont *item1 = cocos2d::MenuItemFont::create("Main Title", CC_CALLBACK_1(GameOverScene::menuItemGoBackCallback, this));
    cocos2d::Menu *mn = cocos2d::Menu::create(item1, NULL);
    mn->alignItemsVertically();
    this->addChild(mn);
    mn->setPosition(cocos2d::Vec2(size.width/2, size.height/4));
    
    return true;
}

void GameOverScene::menuItemGoBackCallback(cocos2d::Ref *pSender) {
    auto indexScene = IndexScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(indexScene);
}

void GameOverScene::GetScore(cocos2d::Ref *sender) {
    score = *((float *)sender);
    
    float highestScore = UserOptions::getInstance()->GetHighestScore();
    if(highestScore < score) {
        UserOptions::getInstance()->SetHighestScore(score);
    }
    
    std::stringstream ss;
    ss<<UserOptions::getInstance()->TransferFormalHighestScore(score);
    
    this->scoreMessage->setString(ss.str());
}

void GameOverScene::CreateCryAnimation() {
    cocos2d::SpriteFrameCache *cache = cocos2d::SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Animation/cry/hero_cry.plist");
    
    cocos2d::Vector<cocos2d::SpriteFrame *> spriteFrames;
    for (int i = 1; i <= 8; i++) {
        std::stringstream ss;
        ss << "hero_cry_" << i << ".png";
        std::string name = ss.str();
        cocos2d::SpriteFrame *frame = cache->getSpriteFrameByName(name);
        spriteFrames.pushBack(frame);
    }
    
    cocos2d::Animation *animation = cocos2d::Animation::createWithSpriteFrames(spriteFrames, 1.0f/8);
    animation->setLoops(-1);
    this->heroCry = cocos2d::Animate::create(animation);
    this->heroCry->retain();
}
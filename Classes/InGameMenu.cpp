//
//  InGameMenu.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/24.
//
//

#include "InGameMenu.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* InGameMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = InGameMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool InGameMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    
    //addChild(rootNode);
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    cocos2d::Sprite *bg = cocos2d::Sprite::create(rMENUBACK);
    bg->setPosition(cocos2d::Vec2(size.width/2, size.height/2));
    addChild(bg);
    
    cocos2d::MenuItemFont::setFontName("Times New Roman");
    cocos2d::MenuItemFont::setFontSize(43);
    
    cocos2d::MenuItemFont *item1 = cocos2d::MenuItemFont::create("Resume Game", CC_CALLBACK_1(InGameMenu::menuItemResumeGameCallback, this));
    cocos2d::MenuItemFont *item2 = cocos2d::MenuItemFont::create("Main Title", CC_CALLBACK_1(InGameMenu::menuItemMainTitleCallback, this));
    cocos2d::Menu *mn = cocos2d::Menu::create(item1, item2, NULL);
    mn->alignItemsVertically();
    this->addChild(mn);
    
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(InGameMenu::onTouchBegan, this);
    
    return true;
}

bool InGameMenu::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    
    return true;
}

void InGameMenu::menuItemResumeGameCallback(cocos2d::Ref *pSender) {
    cocos2d::Director::getInstance()->popScene();
}

void InGameMenu::menuItemMainTitleCallback(cocos2d::Ref *pSender) {
// pass
    //cocos2d::Director::getInstance()->popScene();
}

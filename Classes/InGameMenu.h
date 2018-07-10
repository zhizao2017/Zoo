//
//  InGameMenu.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/24.
//
//

#ifndef InGameMenu_h
#define InGameMenu_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"

class InGameMenu: public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(InGameMenu);
    
private:
    void menuItemResumeGameCallback(cocos2d::Ref *pSender);
    void menuItemMainTitleCallback(cocos2d::Ref *pSender);
    
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
};

#endif /* InGameMenu_h */

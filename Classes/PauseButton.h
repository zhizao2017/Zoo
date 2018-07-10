//
//  PauseButton.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/24.
//
//

#ifndef PauseButton_h
#define PauseButton_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"
#include "InGameMenu.h"
#include "BlankScene.h"

class PauseButton: public cocos2d::Sprite {
public:
    PauseButton(){};
    ~PauseButton(){};
    
    static PauseButton *CreateSpriteWithFrame();
    
    CREATE_FUNC(PauseButton);

    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

private:

    void InitPauseButton();
    
    cocos2d::Rect buttonRect;
};

#endif /* PauseButton_h */

//
//  BlankScene.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/25.
//
//

#ifndef BlankScene_h
#define BlankScene_h

#include <stdio.h>
#include "cocos2d.h"

class BlankScene: public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(BlankScene);
private:
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
};

#endif /* BlankScene_h */

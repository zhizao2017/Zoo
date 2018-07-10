//
//  GameOverScene.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/27.
//
//

#ifndef GameOverScene_h
#define GameOverScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"
#include "UserOptions.h"
#include "IndexScene.h"

class GameOverScene: public cocos2d::Scene {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static GameOverScene* createScene(float score);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    
    void CreateCryAnimation();

    void menuItemGoBackCallback(cocos2d::Ref *pSender);
    
    float score;
    
    GameOverScene(float score);
private:
    
    //cocos2d::Label *gameOverMessage;
    cocos2d::Label *scoreMessage;
    cocos2d::Animate *heroCry;
    
    cocos2d::Menu *mn;
    
    cocos2d::Sprite *hero;
    
    void GetScore(cocos2d::Ref *sender);
};

#endif /* GameOverScene_h */

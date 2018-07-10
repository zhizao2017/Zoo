//
//  StatusBar.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/2/20.
//
//

#ifndef StatusBar_h
#define StatusBar_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"
#include "UserOptions.h"

class StatusBar: public cocos2d::Sprite {
public:
    StatusBar(){};
    ~StatusBar(){};
    
    static StatusBar *CreateSpriteWithFrame();
    
    CREATE_FUNC(StatusBar);
    
    void SetHeroObjective(transistorType type);
    void SetRemainedTime(std::string str);
    
    void update(float delta);
    void updateRemaidTime(float time){remaindTime = time;};
    
    bool IsGameOver(){return isGameOver;};
    bool isNearlyEnd = false;
    
    void NearlyAnimationEnd();
    
    void SetScore(float score);
private:
    void InitStatusBar();
    float remaindTime;
    
    cocos2d::Sprite *heroAvatar;
    cocos2d::ProgressTimer *progressTimer;
    
    cocos2d::Sprite *heroObjective;
    cocos2d::Label *objectiveLabel;
    
    cocos2d::Label *highestScoreLabel;
    cocos2d::Label *highestScore;
    
    cocos2d::Label *currentScoreLabel;
    cocos2d::Label *currentScore;
    
    bool isGameOver;
};

#endif /* StatusBar_h */

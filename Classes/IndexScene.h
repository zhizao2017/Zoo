//
//  IndexScene.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#ifndef IndexScene_h
#define IndexScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "GameScene.h"

class IndexScene: public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(IndexScene);
    
    void menuItemStartGameCallback(cocos2d::Ref *pSender);
    void menuItemCreditsCallback(cocos2d::Ref *pSender);
    
    void InitHeroAnimation();
    cocos2d::Animation *CreateAnimation(const char *resourcePath, const char *prefix, int frameCount, float delay, bool isLoops);
    
    void CreateTutorialAnimation();
    void DoTutorialAnimation();
    void ScaleAnimationEnd();
    void BonusAnimationEnd();
    
    void ResetStatus();
    
    void MainLoop(float delta);
    
private:
    cocos2d::Sprite *hero;
    cocos2d::Sprite *obj;
    cocos2d::Label *bonusLabel;
    
    cocos2d::Label *band;
    
    cocos2d::ccBezierConfig configPoint;
    
    cocos2d::Animate *heroCry;
    cocos2d::Animate *heroEat;
    cocos2d::Animate *heroFly;
    cocos2d::Animate *heroLaugh;
    
    bool isMove;
    bool isHold;
    int currentEpisode;
    
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    void onContactSeperate(cocos2d::PhysicsContact &contact);
    
    cocos2d::Vec2 heroPos;
    cocos2d::Vec2 objPos;
    
    cocos2d::Vec2 tutorialLeftPoint;
    cocos2d::Vec2 tutorialRightPoint;
    cocos2d::Vec2 tutorialMidPoint;
};

#endif /* IndexScene_h */

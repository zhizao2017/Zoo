//
//  GameScene.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#ifndef GameScene_h
#define GameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"
#include "Hero.h"
#include "Capsule.h"
#include "NormalCapsule.h"
#include "EnhancedCapsule.h"
#include "SeniorRD.h"
#include "JuniorRD.h"
#include "Transistor.h"
#include "SlideDirection.h"
#include "GameCenter.h"
#include "StatusBar.h"
#include "PauseButton.h"
#include "GameOverScene.h"
#include "Bubble.h"
#include "UserOptions.h"

class GameScene: public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
private:
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    void onContactSeperate(cocos2d::PhysicsContact &contact);
    
    bool IsWall(int tag);
    
    void InitGameScene();
    
    cocos2d::Vec2 beginTouchPoint;
    cocos2d::Vec2 previousTouchPoint;
    cocos2d::Vec2 currentTouchPoint;
    
    GameCenter *gameCenter;
    
    Hero *hero;
    
    void SystemClocker(float delta);
    void MainLoop(float delta);
    void PatternReadySchdule(float delta);
    void PatternNormalSchdule(float delta);
    void PatternNormalEndSchdule(float delta);
    void PatternEnhancedSchdule(float delta);
    void changeTargetUpdate(float delta);
    //void enhancedDifficult(float delta);
    void EachFrameActivity(float delta);
    void CreateTransistorSchdule(float delta);
    void CreateNorCapsuleSchdule(float delta);
    void CreateEnhancedCapsuleSchdule(float delta);
    
    cocos2d::Node *edge1;
    cocos2d::Node *edge2;
    cocos2d::Node *edge3;
    cocos2d::Node *edge4;

    float heroPosition();
    
    void GameOver(Ref* sender);
    
    void CreateNormalCapsule();
    void CreateEnhancedCapsule();
    void CreateTransistor();
    
    JuniorRD *jr;
    SeniorRD *sr;
    
    StatusBar *statusBar;
    PauseButton *pauseButton;
    cocos2d::Label *bonusPunishLabel;
    
    Bubble *rightBubble;
    Bubble *leftBubble;
    
    float systemClock;
    float PatternNEClock;
    
    Pattern currentPattern;
};


#endif /* GameScene_h */

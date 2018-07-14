//
//  GameScene.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#include "GameScene.h"

cocos2d::Scene* GameScene::createScene() {
    auto scene = cocos2d::Scene::createWithPhysics();
    cocos2d::Vect gravity = cocos2d::Vect(0, 0);
    scene->getPhysicsWorld()->setGravity(gravity);
    //scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

void GameScene::GameOver(Ref* sender){

}

bool GameScene::init() {
    if ( !Layer::init()) {
        return false;
    }
    
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    cocos2d::Sprite *backGround = cocos2d::Sprite::create(rBACKGROUND);
    backGround->setPosition(cocos2d::Vec2(size.width/2, size.height/2));
    addChild(backGround);
    
    this->gameCenter = new GameCenter();
    InitGameScene();
 
    this->hero = Hero::CreateSpriteWithFrame(rHERO);
#warning Method
    this->hero->setPosition(cocos2d::Vec2(size.width/2, size.height/2));
    this->hero->SetPreviousTouchPoint(cocos2d::Vec2(size.width/2, size.height/2));
    this->addChild(this->hero);
    this->gameCenter->SetHero(this->hero);
        
    this->jr = JuniorRD::CreateJuniorRDSprite();
    addChild(jr);
    this->sr = SeniorRD::CreateSeniorRDSprite();
    addChild(sr);
    
    this->statusBar = StatusBar::CreateSpriteWithFrame();
    this->addChild(statusBar);
    
    this->bonusPunishLabel = cocos2d::Label::create();
    addChild(bonusPunishLabel);
    
    this->pauseButton = PauseButton::CreateSpriteWithFrame();
    addChild(pauseButton);
    
    this->rightBubble = Bubble::CreateSpriteWithFrame(BRight);
    cocos2d::Vec2 jrPos = jr->getPosition();
    this->rightBubble->setPosition(cocos2d::Vec2(jrPos.x-35, jrPos.y+jr->getContentSize().height/2+50));
    addChild(this->rightBubble);
    
    this->leftBubble = Bubble::CreateSpriteWithFrame(BLeft);
    cocos2d::Vec2 srPos = sr->getPosition();
    this->leftBubble->setPosition(cocos2d::Vec2(srPos.x+35, srPos.y+sr->getContentSize().height/2+50));
    addChild(this->leftBubble);
    
    auto touchEventListener = cocos2d::EventListenerTouchOneByOne::create();
    touchEventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchEventListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchEventListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener, this);
    cocos2d::EventListenerPhysicsContact *contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    cocos2d::__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(GameScene::GameOver), mGameOver, NULL);
    
    systemClock = 0;
    
    this->schedule(schedule_selector(GameScene::SystemClocker), 1.0f/60);
    this->schedule(schedule_selector(GameScene::MainLoop), 1.0f/60);
    this->schedule(schedule_selector(GameScene::PatternReadySchdule), 1.0f/60);
    this->schedule(schedule_selector(GameScene::changeTargetUpdate), 3.0f);
    
    this->currentPattern = PReady;
    
    return true;
}

void GameScene::SystemClocker(float delta) {
    systemClock += delta;
}

void GameScene::MainLoop(float delta) {
    if (systemClock >= 2 && this->currentPattern == PReady) {
        currentPattern = PNormal;
        this->rightBubble->setVisible(false);
        this->unschedule(schedule_selector(GameScene::PatternReadySchdule));
        
        this->schedule(schedule_selector(GameScene::PatternNormalSchdule), 1.0f/60);
        this->schedule(schedule_selector(GameScene::CreateTransistorSchdule), 2.0f);
        this->schedule(schedule_selector(GameScene::CreateNorCapsuleSchdule), 3.0f);
    }
    if (gameCenter->IsFinalScene() && this->currentPattern == PNormal) {
        this->unschedule(schedule_selector(GameScene::CreateTransistorSchdule));
        this->unschedule(schedule_selector(GameScene::CreateNorCapsuleSchdule));
        this->currentPattern = PNormalEnd;
        PatternNEClock = 0;
        this->unschedule(schedule_selector(GameScene::PatternNormalSchdule));
        this->schedule(schedule_selector(GameScene::PatternNormalEndSchdule), 1.0f/60);
        
        this->schedule(schedule_selector(GameScene::CreateTransistorSchdule), 2.0f);
        this->schedule(schedule_selector(GameScene::CreateNorCapsuleSchdule), 3.0f);
        this->schedule(schedule_selector(GameScene::CreateEnhancedCapsuleSchdule), 2.0f);
    }
    statusBar->SetScore(gameCenter->GetScore());
}

void GameScene::CreateTransistorSchdule(float delta) {
    CreateTransistor();
}

void GameScene::CreateNorCapsuleSchdule(float delta) {
    CreateNormalCapsule();
}

void GameScene::CreateEnhancedCapsuleSchdule(float delta) {
    CreateEnhancedCapsule();
}

void GameScene::PatternReadySchdule(float delta) {
    this->rightBubble->setVisible(true);
    this->rightBubble->SetMessage("System...Ready");
}

void GameScene::PatternNormalSchdule(float delta) {
    EachFrameActivity(delta);
    //this->schedule(schedule_selector(GameScene::CreateTransistorSchdule), 2.0f);
    //this->schedule(schedule_selector(GameScene::CreateNorCapsuleSchdule), 3.0f);
}

void GameScene::PatternEnhancedSchdule(float delta) {
    EachFrameActivity(delta);
    //this->schedule(schedule_selector(GameScene::CreateTransistorSchdule), 2.0f);
    //this->schedule(schedule_selector(GameScene::CreateNorCapsuleSchdule), 3.0f);
    //this->schedule(schedule_selector(GameScene::CreateEnhancedCapsuleSchdule), 2.0f);
}

void GameScene::PatternNormalEndSchdule(float delta){
    
    if (PatternNEClock >= 0 && PatternNEClock < 1) {
        this->rightBubble->SetMessage("OMG...Bugs...");
        this->rightBubble->setVisible(true);
    } else if (PatternNEClock >= 1 && PatternNEClock < 2) {
        this->rightBubble->setVisible(false);
        this->leftBubble->setVisible(true);
        this->leftBubble->SetMessage("Hey.Hold On,Guy");
    } else if (PatternNEClock >= 2 && PatternNEClock < 3) {
        this->rightBubble->setVisible(true);
        this->rightBubble->SetMessage("Okay");
        this->leftBubble->setVisible(false);
    } else if (PatternNEClock >= 3) {
        currentPattern = PEnhanced;
        this->rightBubble->setVisible(false);
        this->leftBubble->setVisible(false);
        this->unschedule(schedule_selector(GameScene::PatternNormalEndSchdule));
        this->schedule(schedule_selector(GameScene::PatternEnhancedSchdule), 1.0f/60);
    }
    PatternNEClock += delta;
}

void GameScene::EachFrameActivity(float delta) {
    if (statusBar->IsGameOver()){
        GameOverScene* gameOverScene = GameOverScene::createScene(gameCenter->GetScore());
        cocos2d::Director::getInstance()->replaceScene(gameOverScene);
    }
    
    gameCenter->IncreaseScore(delta);
    gameCenter->updateHeroPosition();
    gameCenter->DecreaseTime(delta);
    this->statusBar->SetHeroObjective(gameCenter->GetTarget());
    this->statusBar->updateRemaidTime(gameCenter->GetRemainedTime());
    cocos2d::Map<int, Transistor *>::iterator pos;
    for (pos = gameCenter->GetTransistors()->begin(); pos != gameCenter->GetTransistors()->end(); pos++) {
        Transistor *transistor = pos->second;
        if (transistor->IsAlive()) {
            transistor->SetTarget(gameCenter->GetTarget());
        }
    }
}

void GameScene::changeTargetUpdate(float delta) {
    this->gameCenter->SetTarget(GameCenter::GenerateRandomTransistorType());
}

void GameScene::CreateTransistor() {
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    Transistor *transistor = Transistor::CreateTransistorSprite();
#warning modify
    float x = cocos2d::random(transistor->GetTransistorSize().width*0.75/2, size.width - transistor->GetTransistorSize().width*0.75/2);
    float y = cocos2d::random(jr->getContentSize().height, size.height*6/7 - transistor->getContentSize().height/2);
    transistor->setPosition(cocos2d::Vec2(x, y));
    addChild(transistor);
    gameCenter->AddTransistor(transistor);
}

void GameScene::CreateNormalCapsule() {
    NormalCapsule *normalCapsule = NormalCapsule::CreateSpriteWithFrame(rCAPSULE);
    #warning Random Position
    float x = cocos2d::random(jr->getPosition().x - 100, jr->getPosition().x - 200);
    float y = cocos2d::random(jr->getPosition().y - 100, jr->getPosition().y + 100);
    normalCapsule->setPosition(x, y);
    addChild(normalCapsule);
    this->gameCenter->AddCapsule(normalCapsule);
}

void GameScene::CreateEnhancedCapsule() {
    EnhancedCapsule *enhancedCapsule = EnhancedCapsule::CreateSpriteWithFrame(rCAPSULE);
    #warning Random Position
    addChild(enhancedCapsule);
    enhancedCapsule->SniffAppearPosition(gameCenter->GetTransistors());
    this->gameCenter->AddCapsule(enhancedCapsule);
}

bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    if (!cocos2d::Director::getInstance()->isPaused()) {
        this->beginTouchPoint = this->convertToWorldSpace(pTouch->getLocation());
        this->hero->SetPreviousTouchPoint(this->beginTouchPoint);
    }
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    this->currentTouchPoint = this->convertToWorldSpace(pTouch->getLocation());
    if (!this->previousTouchPoint.equals(this->currentTouchPoint)) {
        this->hero->MoveTo(this->currentTouchPoint);
    }
    this->previousTouchPoint = this->currentTouchPoint;
    hero->SetPreviousTouchPoint(this->currentTouchPoint);
}

void GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
    gameCenter->DoContact(contact);
    return true;
}

void GameScene::onContactSeperate(cocos2d::PhysicsContact &contact) {
    
}

void GameScene::InitGameScene() {
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    this->edge1 = cocos2d::Node::create();
    this->edge2 = cocos2d::Node::create();
    this->edge3 = cocos2d::Node::create();
    this->edge4 = cocos2d::Node::create();
    
    edge1->setPhysicsBody(cocos2d::PhysicsBody::createEdgeSegment(cocos2d::Vec2(0, 0), cocos2d::Vec2(0, size.height)));
    edge1->getPhysicsBody()->setCategoryBitmask(0x02);
    edge1->getPhysicsBody()->setContactTestBitmask(0x07);
    edge1->getPhysicsBody()->setCollisionBitmask(0);
    edge1->setTag(kEdge1);
    edge2->setPhysicsBody(cocos2d::PhysicsBody::createEdgeSegment(cocos2d::Vec2(0, size.height), cocos2d::Vec2(size.width, size.height)));
    edge2->getPhysicsBody()->setCategoryBitmask(0x02);
    edge2->getPhysicsBody()->setContactTestBitmask(0x07);
    edge2->getPhysicsBody()->setCollisionBitmask(0);
    edge2->setTag(kEdge2);
    edge3->setPhysicsBody(cocos2d::PhysicsBody::createEdgeSegment(cocos2d::Vec2(size.width, 0), cocos2d::Vec2(size.width, size.height)));
    edge3->getPhysicsBody()->setCategoryBitmask(0x02);
    edge3->getPhysicsBody()->setContactTestBitmask(0x07);
    edge3->getPhysicsBody()->setCollisionBitmask(0);
    edge3->setTag(kEdge3);
    edge4->setPhysicsBody(cocos2d::PhysicsBody::createEdgeSegment(cocos2d::Vec2(0, 0), cocos2d::Vec2(size.width, 0)));
    edge4->getPhysicsBody()->setCategoryBitmask(0x02);
    edge4->getPhysicsBody()->setContactTestBitmask(0x07);
    edge4->getPhysicsBody()->setCollisionBitmask(0);
    edge4->setTag(kEdge4);
    
    addChild(edge1);
    addChild(edge2);
    addChild(edge3);
    addChild(edge4);
}

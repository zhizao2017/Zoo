//
//  GameCenter.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#include "GameCenter.h"

GameCenter::GameCenter():capsuleIndex(10000), transistorIndex(20000), isFinalScene(false), atenTransistor(0), playerScore(0) {
    this->transistorSet = new cocos2d::Map<int, Transistor *>();
    this->capsuleSet = new cocos2d::Map<int, Capsule *>();
    
    heroTarget = GenerateRandomTransistorType();
    ResetTime();
}

void GameCenter::DecreaseTime(float delta) {
    remainedTime -= delta;
    if (remainedTime <= 0) {
        cocos2d::__NotificationCenter::getInstance()->postNotification(mGameOver);
    }
}

contactType GameCenter::SniffContactType(int tagA, int tagB) {
    if (IsACapsule(tagA) && IsAEdge(tagB)) {
        switch (tagB) {
            case kEdge1:
                return CapsuleEdge1;
            case kEdge2:
                return CapsuleEdge2;
            case kEdge3:
                return CapsuleEdge3;
            case kEdge4:
                return CapsuleEdge4;
            default:
                return NoneContact;
        }
    } else if (IsACapsule(tagB) && IsAEdge(tagA)) {
        switch (tagA) {
            case kEdge1:
                return Edge1Capsule;
            case kEdge2:
                return Edge2Capsule;
            case kEdge3:
                return Edge3Capsule;
            case kEdge4:
                return Edge4Capsule;
            default:
                return NoneContact;
        }
    } else if (IsATransistor(tagA) && IsAEdge(tagB)){
        switch (tagB) {
            case kEdge1:
                return TransistorEdge1;
            case kEdge2:
                return TransistorEdge2;
            case kEdge3:
                return TransistorEdge3;
            case kEdge4:
                return TransistorEdge4;
            default:
                return NoneContact;
        }
    } else if (IsATransistor(tagB) && IsAEdge(tagA)) {
        switch (tagA) {
            case kEdge1:
                return Edge1Transistor;
            case kEdge2:
                return Edge2Transistor;
            case kEdge3:
                return Edge3Transistor;
            case kEdge4:
                return Edge4Transistor;
            default:
                return NoneContact;
        }
    } else if (IsATransistor(tagA) && IsHero(tagB)) {
        return TransistorHero;
    } else if (IsHero(tagA) && IsATransistor(tagB)) {
        return HeroTransistor;
    } else if (IsACapsule(tagA) && IsHero(tagB)) {
        return CapsuleHero;
    } else if (IsHero(tagA) && IsACapsule(tagB)) {
        return HeroCapsule;
    } else if (IsHero(tagA) && IsAEdge(tagB)) {
        return HeroEdge;
    } else if (IsHero(tagB) && IsAEdge(tagA)) {
        return EdgeHero;
    } else {
        return NoneContact;
    }
}

void GameCenter::EatTransistor() {
    atenTransistor++;
    if (atenTransistor > 5 && !isFinalScene){
        isFinalScene = true;
    }
}

void GameCenter::DoContact(cocos2d::PhysicsContact &contact) {
    int tagA = contact.getShapeA()->getBody()->getNode()->getTag();
    int tagB = contact.getShapeB()->getBody()->getNode()->getTag();
    contactType type = SniffContactType(tagA, tagB);
    if (type == HeroCapsule) {
        Capsule *capsule = GetCapsule(tagB);
        if (capsule->IsAlive()) {
            if (!hero->IsPunished()) {
                PerformCapsuleBeatHeroAnimation(capsule);
            } else {
                capsule->Dead();
                capsule->setVisible(false);
                capsule->removeFromParent();
            }
#warning modify
            remainedTime -= 10.0f;
        }
    } else if (type == CapsuleHero) {
        Capsule *capsule = GetCapsule(tagA);
        if (capsule->IsAlive()) {
            if (!hero->IsPunished()) {
                PerformCapsuleBeatHeroAnimation(capsule);
            } else {
                capsule->Dead();
                capsule->setVisible(false);
                capsule->removeFromParent();
            }
#warning modify
            remainedTime -= 10.0f;
        }
    } else if (type == HeroTransistor) {
        Transistor *transistor = GetTransistor(tagB);
        if (!hero->IsPunished()) {
            if (transistor->IsAlive() && transistor->IsEdible()) {
                if (transistor->GetTransistorType() == heroTarget) {
                    TransistorBonus();
                    transistor->PerformBounsAnimation();
                    PerformHeroEatTransistorAnimation(transistor, true);
                } else {
                    TransistorPunish();
                    transistor->PerformPunishAnimation();
                    PerformHeroEatTransistorAnimation(transistor, false);
                }
                EatTransistor();
            }
        }
    } else if (type == TransistorHero) {
        Transistor *transistor = GetTransistor(tagA);
        if (!hero->IsPunished()) {
            if (transistor->IsAlive() && transistor->IsEdible()) {
                if (transistor->GetTransistorType() == heroTarget) {
                    TransistorBonus();
                    transistor->PerformBounsAnimation();
                    PerformHeroEatTransistorAnimation(transistor, true);
                } else {
                    TransistorPunish();
                    transistor->PerformPunishAnimation();
                    PerformHeroEatTransistorAnimation(transistor, false);
                }
                EatTransistor();
            }
        }
    } else if (type == HeroEdge || type == EdgeHero) {

    }
}

transistorType GameCenter::GenerateRandomTransistorType() {
    return cocos2d::rand_0_1() < 0.5?TZero:TOne;
}

void GameCenter::TransistorPunish() {
    remainedTime -= 5.0f;
    if (!isFinalScene) {
#warning Animation
        isFinalScene = true;
    }
}

void GameCenter::TransistorBonus() {
    remainedTime += 2.0f;
}

void GameCenter::PerformCapsuleBeatHeroAnimation(Capsule *capsule) {
    if (hero != NULL && capsule != NULL) {
        hero->DoCrying();
        capsule->Dead();
        capsule->setVisible(false);
        capsule->removeFromParent();
    }
}

void GameCenter::PerformHeroEatTransistorAnimation(Transistor *transistor, bool isBonus) {
    if (hero != NULL && transistor != NULL) {
        hero->DoEating(isBonus);
    }
}

void GameCenter::updateHeroPosition() {
    cocos2d::Map<int, Capsule *>::iterator pos;
    for (pos = capsuleSet->begin(); pos != capsuleSet->end(); pos++) {
        Capsule *capsule = pos->second;
        capsule->RequestHeroPosition(hero);
    }
}
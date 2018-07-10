//
//  UserOptions.cpp
//  OneOrZero
//
//  Created by 魏琪 on 16/3/9.
//
//

#include "UserOptions.h"

UserOptions *UserOptions::instance = new UserOptions();

UserOptions::UserOptions() {
    highestScore = cocos2d::UserDefault::getInstance()->getFloatForKey("HighestScore", -1);
    if (highestScore == -1) {
        cocos2d::UserDefault::getInstance()->setFloatForKey("HighestScore", 0);
    }
}

UserOptions *UserOptions::getInstance() {
    return instance;
}

void UserOptions::SetHighestScore(float score) {
    highestScore = score;
    cocos2d::UserDefault::getInstance()->setFloatForKey("HighestScore", score);
}

std::string UserOptions::GetFormalHighestScore() {
    int minute = (int)highestScore/60;
    int second = highestScore - minute*60;
    std::stringstream ss;
    ss<<minute<<"'"<<second<<"\"";
    return ss.str();
}

std::string UserOptions::TransferFormalHighestScore(float score) {
    int minute = (int)score/60;
    int second = score - minute*60;
    std::stringstream ss;
    ss<<minute<<"'"<<second<<"\"";
    return ss.str();
}
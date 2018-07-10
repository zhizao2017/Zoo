//
//  UserOptions.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/3/9.
//
//

#ifndef UserOptions_h
#define UserOptions_h

#include <stdio.h>
#include "cocos2d.h"

class UserOptions {
public:
    static UserOptions *getInstance();
    
    float GetHighestScore() const{return highestScore;};
    void SetHighestScore(float score);
    std::string GetFormalHighestScore();
    std::string TransferFormalHighestScore(float score);
private:
    UserOptions();
    ~UserOptions();
    
    static UserOptions *instance;
    float highestScore;
};

#endif /* UserOptions_h */

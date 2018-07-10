//
//  Bubble.hpp
//  OneOrZero
//
//  Created by 魏琪 on 16/3/5.
//
//

#ifndef Bubble_h
#define Bubble_h

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"

enum BubbleType {
    BLeft,
    BRight
};

class Bubble: public cocos2d::Sprite {
public:
    Bubble(){};
    ~Bubble(){};
    
    static Bubble *CreateSpriteWithFrame(BubbleType type);
    
    void SetMessage(std::string str){this->message->setString(str);};
    
    CREATE_FUNC(Bubble);
private:
    
    void InitBubble(BubbleType type);
    cocos2d::Label *message;
};

#endif /* Bubble_h */

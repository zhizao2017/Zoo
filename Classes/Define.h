//
//  Define.h
//  OneOrZero
//
//  Created by 魏琪 on 16/1/19.
//
//

#ifndef Define_h
#define Define_h

// resource
//const char *rBACKGROUND = "background.png";
//const char *rHERO = "hero.png";
#define rBACKGROUND "background.png"
#define rMENUBACK "background_menu.png"
#define rHERO "hero.png"
#define rAvatar "hero_avatar.png"
#define rAvatarFill "hero_avatar_fill.png"
#define rCAPSULE "capsule.png"
#define rTRANSISTORZERO "transistor_zero.png"
#define rTRANSISTORONE "transistor_one.png"
#define rSeniorRD "senior_RD.png"
#define rJuniorRD "junior_RD.png"
#define rPause "pause_button.png"
#define rLeftBubble "bubble_left.png"
#define rRightBubble "bubble_right.png"
#define mGameOver "game_over"


const int kEdge1 = 1;
const int kEdge2 = 2;
const int kEdge3 = 3;
const int kEdge4 = 4;
const int kHero = 5;
const int kCapulse = 6;
const int kTransistor = 7;

const int aFlyLeft = 100;
const int aFlyRight = 101;
const int aFlyUp = 102;
const int aFlyDown = 103;
const int aEat = 104;
const int aLaugh = 105;
const int aCry = 106;

enum transistorType {
    TZero,
    TOne
};

enum Pattern {
    PReady,
    PNormal,
    PNormalEnd,
    PEnhanced
};

#endif /* Define_h */

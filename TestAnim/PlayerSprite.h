//
//  PlayerSprite.h
//  TestAnim
//
//  Created by 杨 仑 on 13-9-24.
//
//

#ifndef __TestAnim__PlayerSprite__
#define __TestAnim__PlayerSprite__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using std::string;
enum kState {
    EInvalid=-1,
    ESitting,//打坐
    EStanding,//站立stand
    EFightStanding,//战斗中站立fightingStand
    ERunning,//行走walk
    ERidingStand,//骑马站立ridingWalk
    ERiding,//骑行riding
    EAttacking,//攻击attack
    EHurting,//受伤hit
    EDeath //死亡dead
};// 人物状态

enum kPathDirection {
    EPathTop = 1,
    EPathTopRight,
    EPathRight,
    EPathBottomRight,
    EPathBottom,
    EPathBottomLeft,
    EPathLeft,
    EPathTopLeft
};

class PlayerSprite:public CCSprite{
private:
    string prefix;
    kState curState = EStanding;
    kPathDirection direction = EPathLeft;
public:
    CREATE_FUNC(PlayerSprite);
    PlayerSprite();
    ~PlayerSprite();
    bool init();
    CCArray* currentFrames();
    void loadResource();
    void stand();
    void run();
    void hurt();
    void death(CCObject* obj, SEL_CallFuncN selector);
};
#endif /* defined(__TestAnim__PlayerSprite__) */

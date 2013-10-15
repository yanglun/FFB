//
//  MainGame.h
//  TestAnim
//
//  Created by 杨 仑 on 13-9-24.
//
//

#ifndef __TestAnim__MainGame__
#define __TestAnim__MainGame__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MainGame:public CCLayerColor{
public:
    MainGame();
    ~MainGame();
    bool init();
    void onEnter();
    void onExit();
    static CCScene* scene();
  	void gameLogic(float dt);
    void updateGame(float dt);
    void addTarget();
    void spriteMoveFinished(CCNode* sender);
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void registerWithTouchDispatcher();
    CREATE_FUNC(MainGame);
private:
    	CCArray *_targets;
        CCArray *_projectiles;
    int _projectilesDestroyed;
};


#endif /* defined(__TestAnim__MainGame__) */

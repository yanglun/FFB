//
//  HPSprite.h
//  xzb
//
//  Created by 姚杰 on 13-5-24.
//
//

#ifndef __xzb__HPSprite__
#define __xzb__HPSprite__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class HPSprite : public CCNode {

public:
    static HPSprite *create(float aHp,float aMaxHp);
    virtual bool init(float aHp,float aMaxHp);
    HPSprite();
    virtual ~HPSprite();
    
    virtual void onEnter();
    virtual void onExit();
    
public:
    void setValue(float aHp);
    
private:
    void show();
    
private:
    CCSprite *bgSprite;
    CCSprite *frontSprite;
    
    float maxValue;
    float curValue;
};


#endif /* defined(__xzb__HPSprite__) */

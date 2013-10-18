//
//  HPSprite.cpp
//  xzb
//
//  Created by 姚杰 on 13-5-24.
//
//

#include "HPSprite.h"

HPSprite *HPSprite::create(float aHp,float aMaxHp){
    HPSprite *ret = new  HPSprite;
    if(ret && ret->init(aHp,aMaxHp)){
        ret->autorelease();
        
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return NULL;
}

bool HPSprite::init(float aHp,float aMaxHp){
    if(CCNode::init()){
        curValue = aHp;
        maxValue = aMaxHp;
        return true;
    }
    
    return false;
}

HPSprite::HPSprite(){
    
}

HPSprite::~HPSprite(){
    
}

void HPSprite::onEnter(){
    CCNode::onEnter();
    
    show();
}

void HPSprite::onExit(){
    CCNode::onExit();
}

void HPSprite::setValue(float aHp){
    curValue = aHp;
    
    show();
}

void HPSprite::show(){
    removeAllChildren();
    
    bgSprite = CCSprite::create("gamesrc/xuetiao/xuetiao-kuang.png");
    bgSprite->setAnchorPoint(CCPointZero);
    bgSprite->setPosition(CCPointZero);
    addChild(bgSprite);
    setContentSize(bgSprite->getContentSize());
    
    frontSprite = CCSprite::create("gamesrc/xuetiao/xuetiao.png");
    frontSprite->setAnchorPoint(ccp(0,.5));
    frontSprite->setPosition(ccp(bgSprite->getContentSize().width/2-bgSprite->getContentSize().width/2,bgSprite->getContentSize().height/2));
    bgSprite->addChild(frontSprite);
    
    if(maxValue > 0){
        float rate = curValue/maxValue;
        CCLog("rate=%f",rate);
        if(rate > 1){
            rate = 1;
        }
        frontSprite->setScaleX(rate);
    }
}

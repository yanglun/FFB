//
//  PlayerSprite.cpp
//  TestAnim
//
//  Created by 杨 仑 on 13-9-24.
//
//

#include "PlayerSprite.h"
#include "AnimateHelper.h"
#include "HPSprite.h"

PlayerSprite::PlayerSprite(){
    prefix = "body_1";
    direction = EPathLeft;
}

PlayerSprite::~PlayerSprite(){
    
}

bool PlayerSprite::init(){
    if (!CCSprite::init()){
        return false;
    }
//   CCLayerColor* colorLayerBg =  CCLayerColor::create(ccc4(255,0,0,255));
//    this->addChild(colorLayerBg,-1);
    loadResource();
    showHp();
    return true;
}

void PlayerSprite::loadResource(){
    
    CCString* plistName = CCString::createWithFormat("gamesrc/body/%s.plist",prefix.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName->getCString());
    this->setContentSize(CCSize(50,80));
}

CCArray *PlayerSprite::currentFrames(){
    CCArray *ret = CCArray::create();
    
    const char *head = prefix.c_str();
    
    
    if(curState == EStanding)
    {
        if(direction == EPathBottom)
        {
            for(int i = 1;i <= 4;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathBottomLeft || direction == EPathBottomRight)
        {
            for(int i = 5;i <= 8;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathLeft || direction == EPathRight)
        {
            for(int i = 9;i <= 12;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathTopLeft || direction == EPathTopRight)
        {
            for(int i = 13;i <= 16;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathTop)
        {
            for(int i = 17;i <= 20;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
    }else if(curState == ERunning)
    {
        if(direction == EPathBottom)
        {
            for(int i = 41;i <= 56;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathBottomLeft || direction == EPathBottomRight)
        {
            for(int i = 57;i <= 72;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathLeft || direction == EPathRight)
        {
            for(int i = 73;i <= 88;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathTopLeft || direction == EPathTopRight)
        {
            for(int i = 89;i <= 104;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathTop)
        {
            for(int i = 105;i <= 120;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
    }else if(curState == EHurting)
    {
        if(direction == EPathBottom)
        {
            for(int i = 161;i <= 164;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathBottomLeft || direction == EPathBottomRight)
        {
            for(int i = 165;i <= 168;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathLeft || direction == EPathRight)
        {
            for(int i = 169;i <= 172;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathTopLeft || direction == EPathTopRight)
        {
            for(int i = 173;i <= 176;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
        else if(direction == EPathTop)
        {
            for(int i = 177;i <= 180;i++)
            {
                CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
                ret->addObject(name);
            }
        }
    }
    else if(curState == EDeath)
    {
        for(int i = 181;i <= 190;i++)
        {
            CCString *name = CCString::createWithFormat("%s%04d.png",head,i);
            ret->addObject(name);
        }
    }
    
    return ret;
}

void PlayerSprite::hurt(){
    stopAllActions();
    curState = EHurting;
    //    checkFlipX();
    //    checkZ();
    CCArray *frames = currentFrames();
    float interval = .04;
    CCAnimate *animate = AnimateHelper::actionWith(frames, interval);
    CCSequence *seq = CCSequence::create(animate,NULL);
    runAction(seq);
}

void PlayerSprite::death(CCObject* obj, SEL_CallFuncN selector){
    stopAllActions();
    curState = EHurting;
    CCArray *frames1 = currentFrames();
    curState = EDeath;
    CCArray *frames2 = currentFrames();
    float interval = .04;
    CCAnimate *animate1 = AnimateHelper::actionWith(frames1, interval);
     CCAnimate *animate2 = AnimateHelper::actionWith(frames2, interval);
    
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( obj,
                                                             selector);
    CCSequence *seq = CCSequence::create(animate1,animate2,actionMoveDone,NULL);
    runAction(seq);
}


void PlayerSprite::stand(){
    stopAllActions();
    CCArray *frames = currentFrames();
    float interval = .15;
    CCAnimate *animate = AnimateHelper::actionWith(frames, interval);
    CCRepeatForever *repeat = CCRepeatForever::create(animate);
    //repeat->setTag(kRepeatAnimationTag);
    runAction(repeat);
}

void PlayerSprite::run(){
    stopAllActions();
    curState = ERunning;
    CCArray *frames = currentFrames();
    float interval = .05;
    CCAnimate *animate = AnimateHelper::actionWith(frames, interval);
    CCRepeatForever *repeat = CCRepeatForever::create(animate);
    runAction(repeat);
}

void PlayerSprite::showHp(){
   
        HPSprite *sprite = HPSprite::create(100, 100);
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(140,220));
//        sprite->setTag(kHpSpriteTag);
        addChild(sprite,6);
  
}

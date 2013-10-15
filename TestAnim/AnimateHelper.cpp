//
//  AnimateHelper.cpp
//  TestAnim
//
//  Created by 杨 仑 on 13-9-11.
//
//

#include "AnimateHelper.h"
#include "Utils.h"

CCAnimate *AnimateHelper::actionWith(CCArray *frameNames,float delay)
{
    CCArray *frames = CCArray::create();
    
    CCObject *pObj = NULL;
    CCARRAY_FOREACH(frameNames, pObj)
    {
        CCString *name = (CCString *)pObj;
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        if(frame)
        {
            frames->addObject(frame);
        }
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames,delay);
    CCAnimate *animate = CCAnimate::create(animation);
    return animate;
}

CCAnimate * AnimateHelper::actionWith(const char *plistName,float delay){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName);
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistName);
    CCDictionary *dict = CCDictionary::createWithContentsOfFile(path.c_str());
    CCDictionary *framesDict = (CCDictionary *)dict->objectForKey("frames");
    if(framesDict)
    {
        int framesCount = framesDict->allKeys()->count();
        CCArray *frames = CCArray::createWithCapacity(framesCount);
        CCArray *allKeys = framesDict->allKeys();
        Utils::sortArray(allKeys);
        CCObject *pObj = NULL;
        CCARRAY_FOREACH(allKeys, pObj){
            CCString *key = (CCString *)pObj;            
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
            if(frame)
            {
                frames->addObject(frame);
            }
        }        
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames,delay);
        CCAnimate *animate = CCAnimate::create(animation);
        return animate;
    }
    
    return NULL;
}
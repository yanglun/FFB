//
//  AnimateHelper.h
//  TestAnim
//
//  Created by 杨 仑 on 13-9-11.
//
//

#ifndef __TestAnim__AnimateHelper__
#define __TestAnim__AnimateHelper__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class AnimateHelper{
public:
    virtual void aa();
    static CCAnimate *actionWith(const char *plistName,float delay);
    static CCAnimate *actionWith(CCArray *frameNames,float delay);
};

#endif /* defined(__TestAnim__AnimateHelper__) */

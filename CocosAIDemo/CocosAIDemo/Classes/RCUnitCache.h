//
//  RCUnitCache.h
//  ComicWars
//
//  Created by Bai Ryan on 13-11-18.
//
//

#ifndef __ComicWars__RCUnitCache__
#define __ComicWars__RCUnitCache__

#include <iostream>
#include "cocos2d.h"
#include "RCUnit.h"

class RCUnitCache : public cocos2d::CCNode {
    
    
public:
    
    RCUnitCache()
    :m_unitCount(0)
    {}
    
    static RCUnitCache *createWithSpriteFrameNameAndKey(const char *frameName, const char *key, int count, AnimationParam *animationParam);
    virtual bool initWithSpriteFrameNameAndKey(const char *frameName, const char *key, int count, AnimationParam *animationParam);
    
    RCUnit *getUnitByIndex(int index);
    
    void addSubFormCacheWithSpriteFrameNameAndKey(const char *frameName, const char *key, AnimationParam *animationParam);
    
    int getUnitCount(){return m_unitCount;}
    
    cocos2d::CCArray *getActiveUnits();
    RCUnit *getNexInactiveUnit();
    
protected:
    cocos2d::CCSpriteBatchNode *m_batchNode;
    int m_unitCount;
};



#endif /* defined(__ComicWars__RCUnitCache__) */

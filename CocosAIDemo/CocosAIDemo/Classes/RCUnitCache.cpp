//
//  RCUnitCache.cpp
//  ComicWars
//
//  Created by Bai Ryan on 13-11-18.
//
//

#include "RCUnitCache.h"

USING_NS_CC;

RCUnitCache *RCUnitCache::createWithSpriteFrameNameAndKey(const char *frameName, const char *key,int count, AnimationParam *animationParam)
{
    RCUnitCache *pRet = new RCUnitCache();
    if (pRet && pRet->initWithSpriteFrameNameAndKey(frameName,key,count, animationParam))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool RCUnitCache::initWithSpriteFrameNameAndKey(const char *frameName, const char *key, int count,AnimationParam *animationParam)
{
    if (!CCNode::init()) {
        return false;
    }
    
    
    m_unitCount = count;
    
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
    m_batchNode = CCSpriteBatchNode::createWithTexture(frame->getTexture());
    addChild(m_batchNode);
    for (int i=0; i<m_unitCount; i++) {
        RCUnit *unit = RCUnit::createWithSpriteFrameNameAndKey(frameName, animationParam, key);
        m_batchNode->addChild(unit);
    }
    return true;
}

RCUnit *RCUnitCache::getUnitByIndex(int index)
{
    CCArray *unitArray = m_batchNode->getChildren();
    RCUnit *unit = (RCUnit *)unitArray->objectAtIndex(index);
    return unit;
}

void RCUnitCache::addSubFormCacheWithSpriteFrameNameAndKey(const char *frameName, const char *key, AnimationParam *animationParam)
{
    CCArray *unitArray = m_batchNode->getChildren();
    for (int i=0; i<m_unitCount; i++) {
        CCObject *object = unitArray->objectAtIndex(i);
        RCUnit *unit = dynamic_cast<RCUnit*>(object);
        
        unit->addSubFormWithSpriteFrameNameAndKey(frameName, animationParam, key);
    }
}

RCUnit *RCUnitCache::getNexInactiveUnit()
{
    CCArray *unitArray = m_batchNode->getChildren();
    RCUnit *unit = NULL;
    for (int i=0; i<m_unitCount; i++) {
        CCObject *object = unitArray->objectAtIndex(i);
        unit = dynamic_cast<RCUnit*>(object);
        if (unit->getIsActive() == false) {
            unit->setIsActive(true);
            return unit;
        }
    }
    return NULL;
}

CCArray *RCUnitCache::getActiveUnits()
{
    CCArray *unitArray = m_batchNode->getChildren();
    
    CCArray *activeUnits = CCArray::create();
    RCUnit *unit = NULL;
    for (int i=0; i<m_unitCount; i++) {
        CCObject *object = unitArray->objectAtIndex(i);
        unit = dynamic_cast<RCUnit*>(object);
        if (unit->getIsActive() == true) {
            activeUnits->addObject(unit);
        }
    }
    return activeUnits;
}










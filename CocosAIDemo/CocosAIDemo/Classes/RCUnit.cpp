//
//  RCUnit.cpp
//  ComicWars
//
//  Created by Bai Ryan on 13-11-18.
//
//

#include "RCUnit.h"

USING_NS_CC;

RCUnit::~RCUnit()
{
    CC_SAFE_RELEASE(m_dictionary);
}

RCUnit *RCUnit::createWithSpriteFrameNameAndKey(const char *frameName, AnimationParam *animationParam, const char *key)
{
    RCUnit *pRet = new RCUnit();
    if (pRet && pRet->initWithSpriteFrameNameAndKey(frameName,animationParam,key))
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

bool RCUnit::initWithSpriteFrameNameAndKey(const char *frameName, AnimationParam *animationParam, const char *key)
{
    if (!CCSprite::initWithSpriteFrameName(frameName)) {
        return false;
    }
    
    m_dictionary = CCDictionary::create();
    m_dictionary->retain();
    
    CCAssert(key != NULL && strcmp(key, "") != 0, "key cant be nil or nothing");

    CCAssert(animationParam, "animation param cant be nil");
    //add animation
    
    CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName(key);
    if (animation == NULL) {
        animation = CCAnimation::create();
        for (int i=1; i <= animationParam->count; i++) {
            CCString *realFrameName = CCString::createWithFormat("%s%.02i.png",animationParam->frameName.c_str(),i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(realFrameName->getCString());
            animation->addSpriteFrame(frame);
        }
        animation->setDelayPerUnit(animationParam->interval);
        animation->setLoops(animationParam->loops);
        animation->setRestoreOriginalFrame(animationParam->restoreFirstFrame);
        
        CCAnimationCache::sharedAnimationCache()->addAnimation(animation, key);
        
    }
    
    m_dictionary->setObject(animation, key);
    CCAnimate *animate = CCAnimate::create(animation);
    m_sequence = animate;
    runAction(m_sequence);
    
    return true;
}

void RCUnit::addSubFormWithSpriteFrameNameAndKey(const char *frameName, AnimationParam *animationParam, const char *key)
{
    //add sprite
    if (!animationParam) {
        return;
    }
    
    CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName(key);
    if (animation == NULL) {
        animation = CCAnimation::create();
        
        for (int i=1; i <= animationParam->count; i++) {
            CCString *realFrameName = CCString::createWithFormat("%s%.02i.png",animationParam->frameName.c_str(),i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(realFrameName->getCString());
            animation->addSpriteFrame(frame);
        }
        animation->setDelayPerUnit(animationParam->interval);
        animation->setLoops(animationParam->loops);
        animation->setRestoreOriginalFrame(animationParam->restoreFirstFrame);
        
        CCAnimationCache::sharedAnimationCache()->addAnimation(animation, key);
    }
    
    m_dictionary->setObject(animation, key);
}

void RCUnit::switchToFormAnimatedByKey(const char *key)
{
    //stopAllActions();
    if (m_sequence) {
        stopAction(m_sequence);
        m_sequence = NULL;
    }
    CCObject* object = m_dictionary->objectForKey(key);
    CCAnimation *animation =  dynamic_cast<CCAnimation*>(object);
    CCAnimate *animate = CCAnimate::create(animation);
    m_sequence = animate;
    runAction(m_sequence);
}

void RCUnit::switchToFormAnimatedByKey(const char *key ,cocos2d::CCCallFunc *callback)
{
    //stopAllActions();
    if (m_sequence) {
        stopAction(m_sequence);
    }

    CCDictElement* el;
    CCDICT_FOREACH(m_dictionary, el)
    {
   //     CCLog("el key:%s",el->getStrKey());
    }
    
    CCObject* object = m_dictionary->objectForKey(key);
    
    
    CCAnimation *animation =dynamic_cast<CCAnimation*>(object);
    CCAnimate *animate = CCAnimate::create(animation);
    m_sequence = CCSequence::create(animate,callback,NULL);
    runAction(m_sequence);
}


CCArray *RCUnit::getAllFormKeys()
{
    return m_dictionary->allKeys();
}

int RCUnit::getFormCount()
{
    return m_dictionary->count();
}

void RCUnit::update(float delta)
{
    CCNode::update(delta);
}

CCRect RCUnit::getUnitRect()
{
    CCRect textureRect = getTextureRect();
    
    float x = getPosition().x - textureRect.size.width/2*getScale();
    float y = getPosition().y - textureRect.size.height/2*getScale();
    float width = textureRect.size.width*getScale();
    float height = textureRect.size.height*getScale();
    
    CCRect rect = CCRectMake(x, y, width, height);
    return rect;
}

void RCUnit::pauseAnimation()
{
    pauseSchedulerAndActions();
}

void RCUnit::resumeAnimation()
{
    resumeSchedulerAndActions();
}





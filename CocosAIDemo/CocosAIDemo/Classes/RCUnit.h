//
//  RCUnit.h
//  ComicWars
//
//  Created by Bai Ryan on 13-11-18.
//
//

#ifndef __ComicWars__RCUnit__
#define __ComicWars__RCUnit__

#include <iostream>
#include "cocos2d.h"

#define kSubFormName "form_name"
#define kSubFromSprite "sprite"
#define kSubFormAnimationKey "aniamtion"

typedef struct
{
    std::string frameName;
    int count;
    int loops;
    bool restoreFirstFrame;
    float interval;
}AnimationParam;

class RCUnit : public cocos2d::CCSprite
{
    
    
public:
    RCUnit():m_dictionary(NULL)
    ,m_isFlipX(false)
    ,m_sequence()
    {
        
    }
    
    ~RCUnit();
    
    static RCUnit *createWithSpriteFrameNameAndKey(const char *frameName, AnimationParam *animationParam, const char *key);
    
    virtual bool initWithSpriteFrameNameAndKey(const char *frameName,AnimationParam *animationParam, const char *key);
    
    void addSubFormWithSpriteFrameNameAndKey(const char *frameName,AnimationParam *animationParam, const char *key);
    
    void switchToFormAnimatedByKey(const char *key);
    void switchToFormAnimatedByKey(const char *key, cocos2d::CCCallFunc *callback);
    
    cocos2d::CCArray *getAllFormKeys();
    
    int getFormCount();
    
    virtual void update(float delta);
    
    cocos2d::CCRect getUnitRect();
    
    void pauseAnimation();
    void resumeAnimation();
    
protected:
    
    cocos2d::CCFiniteTimeAction *m_sequence;
    
    CC_SYNTHESIZE(bool, m_isFlipX, IsFlipX);
    CC_SYNTHESIZE(bool, m_isActive, IsActive);
    
    cocos2d::CCDictionary *m_dictionary;
};



#endif /* defined(__ComicWars__RCUnit__) */

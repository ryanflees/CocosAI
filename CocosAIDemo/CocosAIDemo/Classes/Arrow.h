//
//  Arrow.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-18.
//
//

#ifndef __CocosAIDemo__Arrow__
#define __CocosAIDemo__Arrow__

#include "cocos2d.h"

USING_NS_CC;

#define kTowerArrowImage "kingdomrush/tower/arrow.png"
#define kTowerArrowCount 50

#define kArrowUseMathFunction 0

enum
{
    kArrowRunningAction = 1
};

class MathFuncion;
class Arrow : public CCSprite
{
public:
    Arrow();
    ~Arrow();
    virtual bool init();
    CREATE_FUNC(Arrow);
    void spawn(const CCPoint& startPoint, const CCPoint& endPoint, float height);
    void spawnAtPosition(const CCPoint& point);
    
    void shootEnd(CCNode* node);
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    virtual void draw();
private:
    CC_SYNTHESIZE_READONLY(bool, m_active, IsActive);
    MathFuncion* m_trailFunction;
    
    CCPoint m_startPoint;
    CCPoint m_endPoint;
    CC_SYNTHESIZE(CCJumpTo*, m_jumpTo, JumpTo);
};

class ArrowCache :public CCNode
{
public:
    ArrowCache();
    virtual ~ArrowCache();
    virtual bool init();
    CREATE_FUNC(ArrowCache);
    virtual void onEnter();
    virtual void onExit();
    Arrow* getNextInactiveNode();
private:    
    CCSpriteBatchNode* m_batchNode;
};

#endif /* defined(__CocosAIDemo__Arrow__) */

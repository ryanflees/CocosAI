//
//  Bandit.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#ifndef __CocosAIDemo__Bandit__
#define __CocosAIDemo__Bandit__

#include "cocos2d.h"
#include "CCArmature.h"
#include "CCArmatureDataManager.h"
#include "RCBehaviorTree.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_AI;

enum
{
    kBanditRunUp = 1,
    kBanditRunLeft,
    kBanditRunRight,
    kBanditRunDown
};

enum
{
    kBanditCondCanRun = 1
};

enum
{
    kBanditActionRun = 1
};

class Bandit :public CCNode
, public BTActionDelegate
, public BTConditionDelegate
{
public:
    Bandit();
    virtual ~Bandit();
    virtual bool init();
    CREATE_FUNC(Bandit);
    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float dt);
    
    virtual int onBehaviorTreeActon(BTAction* action);
    
    virtual int onCheckCondition(BTCondition *condition);
    
    void spawnAtPosition(CCPoint pos);
    void setInactive();
private:
    void addArmature();
    CCArmature* m_armature;
    
    void run(int direction);
    void halt(int direction);
    
    CC_PROPERTY(int, m_direction, Direction);
    
    CC_SYNTHESIZE_READONLY(bool, m_isActive, IsActive);
    CC_SYNTHESIZE_READONLY(BTParallel*, m_behavior, Behavior);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCPoint, m_velocity, Velocity);
};


#endif /* defined(__CocosAIDemo__Bandit__) */

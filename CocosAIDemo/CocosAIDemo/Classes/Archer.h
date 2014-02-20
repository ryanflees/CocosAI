//
//  Archer.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#ifndef __CocosAIDemo__Archer__
#define __CocosAIDemo__Archer__

#include  "cocos2d.h"
#include "CCArmature.h"
#include "CCArmatureDataManager.h"
#include "RCBehaviorTree.h"

USING_NS_CC_EXT;
USING_NS_CC;
USING_NS_AI;

enum
{
    kArcherShootDownLeft = 0,
    kArcherShootDownRight,
    kArcherShootTopLeft,
    kArcherShootTopRight
};

enum
{
    kArcherStanceDownLeft = 0,
    kArcherStanceDownRight,
    kArcherStanceTopLeft,
    kArcherStanceTopRight
};

enum
{
    kArcherCondNoEnemySpotted = 1,
    kArcherCondEnemyInsight
};

enum
{
    kArcherActionSwitchStance = 1,
    kArcherActionAttack
};

class Archer;
class ArcherDelegate
{
public:
    virtual CCNode* getAttackTarget(Archer* archer) = 0;
    virtual void shootAtTarget(Archer* archer, CCNode* target) = 0;
};

class Archer :public CCNode
    , public BTActionDelegate
    , public BTConditionDelegate
{
public:
    Archer();
    virtual ~Archer();
    virtual bool init();
    CREATE_FUNC(Archer);
    virtual void onEnter();
    virtual void onExit();
    
    virtual int onBehaviorTreeActon(BTAction* action);
    
    virtual int onCheckCondition(BTCondition* condition);
    
    virtual void update(float dt);
    
    
private:
    void addArmature();
    CCArmature* m_armature;
    void shoot(int direction);
    void switchStance(int stance);
    
    void stanceFinished(CCNode* node, void* data);
    void shootFinished(CCNode* node, void* data);
    
    void attackTarget();
    
    CC_SYNTHESIZE_READONLY(bool, m_attacking, IsAttacking);
    
    CC_SYNTHESIZE(ArcherDelegate*, m_delegate, Delegate);
    CC_SYNTHESIZE_READONLY(BTParallel*, m_behavior, Behavior);
    
    CC_SYNTHESIZE(CCNode*, m_attackTarget, AttackTarget);
    CC_SYNTHESIZE_READONLY(float, m_range, Range);
};

#endif /* defined(__CocosAIDemo__Archer__)*/

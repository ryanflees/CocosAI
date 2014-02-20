//
//  Archer.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#include "Archer.h"
#include "cocos-ext.h"

#define kArcherRange 200

Archer::Archer():m_delegate()
,m_behavior()
,m_attackTarget()
,m_range(kArcherRange)
,m_attacking(false)
{

}

Archer::~Archer()
{
    m_behavior->release();
}

bool Archer::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    m_behavior = BTParallel::create();
    m_behavior->retain();
    
    addArmature();
    return true;
}

void Archer::onEnter()
{
    CCNode::onEnter();
    scheduleUpdate();
}

void Archer::onExit()
{
    CCNode::onExit();
    unscheduleUpdate();
}

void Archer::update(float dt)
{
    if (m_behavior) {
        m_behavior->behave();
    }
}

void Archer::addArmature()
{
    // adding armature to batchnode is not supported in cocos2d-x 2.1.5 yet
    m_armature = CCArmature::create("Tower");
    m_armature->setScale(2.0f);
    addChild(m_armature);
    shoot(kArcherShootDownLeft);
}

void Archer::shoot(int direction)
{
    //CCLog("shoot direction %i",direction);
    if (direction == kArcherShootDownLeft) {
        m_armature->getAnimation()->play("shoot_down_left");
    }
    else if (direction == kArcherShootDownRight)
    {
        m_armature->getAnimation()->play("shoot_down_right");
    }
    else if (direction == kArcherShootTopRight)
    {
        m_armature->getAnimation()->play("shoot_top_right");
    }
    else if (direction == kArcherShootTopLeft)
    {
        m_armature->getAnimation()->play("shoot_top_left");
    }
}

void Archer::switchStance(int stance)
{
    if (stance == kArcherStanceDownLeft) {
        m_armature->getAnimation()->play("stance_down_left");
    }
    else if (stance == kArcherStanceDownRight)
    {
        m_armature->getAnimation()->play("stance_down_right");
    }
    else if (stance == kArcherStanceTopLeft)
    {
        m_armature->getAnimation()->play("stance_top_left");
    }
    else if (stance == kArcherStanceTopRight)
    {
        m_armature->getAnimation()->play("stance_top_right");
    }
}

int Archer::onBehaviorTreeActon(BTAction* action)
{
    if (action->getTag() == kArcherActionSwitchStance) {
        int stance = arc4random()%4;
        switchStance(stance);
        
        float stanceDuration = 3.0f;
        stanceDuration = stanceDuration + (arc4random()%2000)/1000.0f;
        CCCallFuncND* callback = CCCallFuncND::create(this, callfuncND_selector(Archer::stanceFinished),action);
        CCFiniteTimeAction* seq = CCSequence::create(CCDelayTime::create(stanceDuration),callback,NULL);
        runAction(seq);
        return kBehavePending;
    }
    else if (action->getTag() == kArcherActionAttack)
    {
        m_attacking = true;
        stopAllActions();
        attackTarget();
#define kArcherShootDelay 1.0f
        float shoodDelay = kArcherShootDelay;
        CCCallFuncND* callback = CCCallFuncND::create(this, callfuncND_selector(Archer::shootFinished),action);
        CCFiniteTimeAction* seq = CCSequence::create(CCDelayTime::create(shoodDelay),callback,NULL);
        runAction(seq);
        return kBehavePending;
    }
    return kBehaveFailure;
}

int Archer::onCheckCondition(BTCondition* condition)
{
    if (condition->getTag() == kArcherCondNoEnemySpotted) {
        if (m_attacking) {
            return kBehaveFailure;
        }
        else
        {
            return kBehaveSuccess;
        }
    }
    else if (condition->getTag() == kArcherCondEnemyInsight)
    {
        m_attackTarget = NULL;
        if (m_delegate) {
            m_attackTarget = m_delegate->getAttackTarget(this);
        }
        if (m_attackTarget) {
            return kBehaveSuccess;
        }
        return kBehaveFailure;
    }
    return kBehaveFailure;
}

void Archer::stanceFinished(CCNode* node, void* data)
{
    BTAction* action = (BTAction*)data;
    if (action) {
        action->actionFinished();
    }
}

void Archer::shootFinished(CCNode* node, void* data)
{
    BTAction* action = (BTAction*)data;
    if (action) {
        action->actionFinished();
    }
    m_attackTarget = NULL;
    m_attacking = false;
}

void Archer::attackTarget()
{
    if (!m_attackTarget) {
        return;
    }
    
    CCPoint pointInWorld = convertToWorldSpace(getPosition());
    CCLog("archer pointInWorld : %f %f", pointInWorld.x, pointInWorld.y);
    CCPoint direction = m_attackTarget->getPosition() - pointInWorld;
    if (direction.x >= 0 && direction.y >= 0)
    {
        shoot(kArcherShootTopRight);
    }
    else if (direction.x < 0 && direction.y >= 0)
    {
        shoot(kArcherShootTopLeft);
    }
    else if (direction.x >= 0 && direction.y < 0)
    {
        shoot(kArcherShootDownRight);
    }
    else if (direction.x < 0 && direction.y < 0)
    {
        shoot(kArcherShootDownLeft);
    }
    if (m_delegate) {
        m_delegate->shootAtTarget(this, m_attackTarget);
    }
}



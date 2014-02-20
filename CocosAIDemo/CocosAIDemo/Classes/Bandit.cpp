//
//  Bandit.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#include "Bandit.h"

Bandit::Bandit():m_isActive(false)
    ,m_direction(kBanditRunRight)
{

}

Bandit::~Bandit()
{
    m_behavior->release();
}

bool Bandit::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    addArmature();
    setVisible(false);
    
    m_behavior = BTParallel::create();
    m_behavior->retain();
    
    m_velocity = CCPointZero;
    
    return true;
}

void Bandit::onEnter()
{
    CCNode::onEnter();
    scheduleUpdate();
}

void Bandit::onExit()
{
    CCNode::onExit();
    unscheduleUpdate();
}

void Bandit::update(float dt)
{
    if (m_isActive) {
        m_behavior->behave();
    }
}

void Bandit::addArmature()
{
    m_armature = CCArmature::create("Bandit");
    m_armature->setScale(2.0f);
    addChild(m_armature);
}

void Bandit::run(int direction)
{
    if (direction == kBanditRunDown) {
        m_armature->getAnimation()->play("run_down");
    }
    else if (direction == kBanditRunLeft) {
        m_armature->getAnimation()->play("run_left");
    }
    else if (direction == kBanditRunRight) {
        m_armature->getAnimation()->play("run_right");
    //    m_armature->getAnimation()->play("run_left");
    }
    else if (direction == kBanditRunUp) {
        m_armature->getAnimation()->play("run_up");
    }
}

void Bandit::halt(int direction)
{

}

void Bandit::spawnAtPosition(CCPoint pos)
{
    setPosition(pos);
    m_isActive = true;
    setVisible(true);
}

int Bandit::onBehaviorTreeActon(BTAction* action)
{
    float speed = 70;
    if (action->getTag() == kBanditActionRun) {
        if (m_direction == kBanditRunLeft) {
            m_velocity = ccp(-speed,0);
        }
        else if(m_direction == kBanditRunRight)
        {
            m_velocity = ccp(speed,0);
        }
        return kBehaveSuccess;
    }
    return kBehaveFailure;
}

int Bandit::onCheckCondition(BTCondition *condition)
{
    if (condition->getTag() == kBanditCondCanRun) {
        return kBehaveSuccess;
    }
    return kBehaveFailure;
}

void Bandit::setInactive()
{
    m_isActive = false;
    m_behavior->resetBehavior();
    setVisible(false);
}

void Bandit::setDirection(int var)
{
    m_direction = var;
    run(m_direction);
}

int Bandit::getDirection()
{
    return m_direction;
}

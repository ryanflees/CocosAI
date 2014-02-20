//
//  Tower.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#include "Tower.h"
#include "Archer.h"
#include "RCBehaviorTree.h"

USING_NS_AI;

Tower::Tower()
{

}

Tower::~Tower()
{

}

bool Tower::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    addTower();
    addArcher();
    return true;
}

void Tower::onEnter()
{
    
    CCNode::onEnter();
}

void Tower::onExit()
{
    CCNode::onExit();
}

void Tower::addTower()
{
    CCSprite *tower = CCSprite::create("kingdomrush/tower/tower.png");
    addChild(tower);
    tower->setScale(2.0f);
}

void Tower::addArcher()
{
    float archerSpaceX = 17.0f;
    for (int i=0; i<ARCHER_COUNT_IN_TOWER; i++) {
        m_archers[i] = Archer::create();
        addChild(m_archers[i]);
        m_archers[i]->setPosition(ccp(-archerSpaceX + i*archerSpaceX*2, 35));
    }
}

void Tower::setArcherBehavior(ArcherDelegate* delegate)
{
    for (int i=0; i<ARCHER_COUNT_IN_TOWER; i++) {
        
        Archer* archer = m_archers[i];
        
        BTParallel* parrallel = archer->getBehavior();
        
        BTSequence* casualSeq = BTSequence::create();
        parrallel->addBTNode(casualSeq);
        BTCondition* noEnemySpottedCond = BTCondition::create();
        noEnemySpottedCond->setTag(kArcherCondNoEnemySpotted);
        noEnemySpottedCond->setDelegate(archer);
        casualSeq->addBTNode(noEnemySpottedCond);
        
        BTAction* switchStance = BTAction::create();
        switchStance->setTag(kArcherActionSwitchStance);
        switchStance->setDelegate(archer);
        casualSeq->addBTNode(switchStance);
        
        BTSequence* attackSeq = BTSequence::create();
        parrallel->addBTNode(attackSeq);
        
        BTCondition* enemyInsightCond = BTCondition::create();
        enemyInsightCond->setTag(kArcherCondEnemyInsight);
        attackSeq->addBTNode(enemyInsightCond);
        enemyInsightCond->setDelegate(archer);
        
        BTAction* attackAction = BTAction::create();
        attackAction->setTag(kArcherActionAttack);
        attackSeq->addBTNode(attackAction);
        attackAction->setDelegate(archer);
        
        archer->setDelegate(delegate);
    }
}


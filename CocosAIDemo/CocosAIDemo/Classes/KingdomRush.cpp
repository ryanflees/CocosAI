//
//  KingdomRush.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#include "KingdomRush.h"
#include "Tower.h"
#include "CCArmatureDataManager.h"
#include "Bandit.h"
#include "func.h"
#include "Arrow.h"

USING_NS_CC_EXT;

#define kBanditCount 10

KingdomRush::KingdomRush()
:m_tower()
{
    CCArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
}

KingdomRush::~KingdomRush()
{
    m_bandits->release();
}

bool KingdomRush::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    loadResource();
    addBackground();
    addTower();
    addBandits();
    
    return true;
}

void KingdomRush::onEnter()
{
    CCNode::onEnter();
    scheduleUpdate();
}

void KingdomRush::onExit()
{
    CCNode::onExit();
    unscheduleUpdate();
}

void KingdomRush::loadResource()
{
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("kingdomrush/tower/Tower0.png", "kingdomrush/tower/Tower0.plist", "kingdomrush/tower/Tower.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("kingdomrush/bandit/Bandit0.png", "kingdomrush/bandit/Bandit0.plist", "kingdomrush/bandit/Bandit.ExportJson");
}

void KingdomRush::addBackground()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create(ccc4(255, 255, 255, 255), screenSize.width, screenSize.height);
    addChild(layer);
}

void KingdomRush::addTower()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    m_tower = Tower::create();
    addChild(m_tower);
    m_tower->setPosition(ccp(screenSize.width/3, screenSize.height/2));
    m_tower->setArcherBehavior(this);
    
    m_arrowCache = ArrowCache::create();
    addChild(m_arrowCache,1);
}

void KingdomRush::addBandits()
{
    m_bandits = CCArray::create();
    m_bandits->retain();
    
    for (int i=0; i<kBanditCount; i++) {
        Bandit* bandit = Bandit::create();
        m_bandits->addObject(bandit);
        addChild(bandit);
        setArcherBehavior(bandit);
    }
}

Bandit* KingdomRush::getNextInactiveBandit()
{
    for (int i=0; i<m_bandits->count(); i++) {
        Bandit* bandit = (Bandit*)m_bandits->objectAtIndex(i);
        if (!bandit->getIsActive()) {
            return bandit;
        }
    }
    return NULL;
}

CCArray* KingdomRush::getActiveBandits()
{
    CCArray* array = CCArray::create();
    for (int i=0; i<m_bandits->count(); i++) {
        Bandit* bandit = (Bandit*)m_bandits->objectAtIndex(i);
        if (bandit->getIsActive()) {
            array->addObject(bandit);
        }
    }
    return array;
}

void KingdomRush::setArcherBehavior(Bandit* bandit)
{
    BTParallel* parrallel = bandit->getBehavior();
    
    BTSequence* runSeq = BTSequence::create();
    parrallel->addBTNode(runSeq);
    
    BTCondition* canRunCond = BTCondition::create();
    runSeq->addBTNode(canRunCond);
    canRunCond->setDelegate(bandit);
    canRunCond->setTag(kBanditCondCanRun);
    
    BTAction* runAct = BTAction::create();
    runSeq->addBTNode(runAct);
    runAct->setTag(kBanditActionRun);
    runAct->setDelegate(bandit);
}

void KingdomRush::update(float dt)
{
    CCNode::update(dt);
    if (arc4random()%100 == 0) {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        Bandit* bandit = getNextInactiveBandit();
        if (bandit) {
            float x;
            float y;
            if (arc4random()%2 == 0) {
                x = screenSize.width + 40;
                y = 400 + arc4random()%30;
                bandit->setDirection(kBanditRunLeft);
            }
            else
            {
                x = -40;
                y = 190 + arc4random()%20;
                bandit->setDirection(kBanditRunRight);
            }
            bandit->spawnAtPosition(ccp(x, y));
        }
    }
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCArray* bandits = getActiveBandits();
    for (int i=0; i<bandits->count(); i++) {
        Bandit* bandit = (Bandit*)bandits->objectAtIndex(i);
        CCPoint pos = bandit->getPosition();
        CCPoint newPos = pos + ccp(bandit->getVelocity().x*dt, bandit->getVelocity().y*dt);
        bandit->setPosition(newPos);
  
        if (bandit->getDirection() == kBanditRunRight) {
            if (bandit->getPosition().x > screenSize.width + 40) {
                bandit->setInactive();
            }
        }
        else if(bandit->getDirection() == kBanditRunLeft)
        {
            if (bandit->getPosition().x < -40) {
                bandit->setInactive();
            }
        }
        
        bandit->setZOrder(screenSize.height - bandit->getPosition().y);
    }
    
    if (m_tower) {
        m_tower->setZOrder(screenSize.height - m_tower->getPosition().y);
    }
}

CCNode* KingdomRush::getAttackTarget(Archer* archer)
{
    CCArray* bandits = getActiveBandits();
    for (int i=0; i<bandits->count(); i++) {
        Bandit* bandit = (Bandit*)bandits->objectAtIndex(i);
        CCPoint archerPosInWorld = archer->convertToWorldSpace(archer->getPosition());
        //CCLog("archerPosInWorld %f %f", archerPosInWorld.x, archerPosInWorld.y);
        if (distanceBetweenPoints(bandit->getPosition(), archerPosInWorld) < archer->getRange()) {
            archer->setAttackTarget(bandit);
            return bandit;
        }
    }
    return NULL;
}

void KingdomRush::shootAtTarget(Archer* archer, CCNode* target)
{
#define kShootDuration 0.5f;
    float shootDuration = kShootDuration;
    float shootHeight = 20;
    CCPoint startPoint = archer->convertToWorldSpace(archer->getPosition());
    CCPoint endPoint = target->getPosition();
    
    
    float higherY = (startPoint.y > endPoint.y)?startPoint.y:endPoint.y;
    shootHeight = higherY-startPoint.y + shootHeight;
    
    CCJumpTo* jump = CCJumpTo::create(shootDuration, endPoint, shootHeight, 1);
    Arrow* arrow = m_arrowCache->getNextInactiveNode();
    if (arrow) {
#if kArrowUseMathFunction
        arrow->spawn(startPoint, endPoint, shootHeight);
#else
        arrow->spawnAtPosition(startPoint);
        CCCallFuncN* callback = CCCallFuncN::create(arrow, callfuncN_selector(Arrow::shootEnd));
        CCFiniteTimeAction* seq = CCSequence::create(jump, CCDelayTime::create(0.4f), callback, NULL);
        arrow->setJumpTo(jump);
        arrow->runAction(seq);
#endif
     }
}


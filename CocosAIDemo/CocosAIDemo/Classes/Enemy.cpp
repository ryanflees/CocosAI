//
//  Enemy.cpp
//  ComicWars
//
//  Created by Bai Ryan on 13-10-13.
//
//

#include "Enemy.h"
#include "Bullet.h"
#include "func.h"

#define EnemyProneReactionTime 1.0f
#define EnemyStandReactionTime 3.0f
#define kEnemyDefaultSpeed 30.0f
#define kEnemyCreepSpeed 15.0f


USING_NS_CC;

Enemy::~Enemy()
{
    m_behavior->release();
}

Enemy* Enemy::createWithSpriteFrameNameAndKey(const char *frameName, AnimationParam *animationParam, const char *key)
{
    Enemy *pRet = new Enemy();
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

bool Enemy::initWithSpriteFrameNameAndKey(const char *frameName, AnimationParam *animationParam, const char *key)
{
    if (!RCUnit::initWithSpriteFrameNameAndKey(frameName,animationParam,key)) {
        return false;
    }
    
    m_fireDelay = 0.5f;
    m_sight = 500.0f;
    m_delegate = NULL;
    
    m_isShooting = false;
    m_isProne = false;
    
    m_behavior = BTParallel::create();
    m_behavior->retain();
    
    return true;
}

void Enemy::loseHealth(float damage)
{
#define kProneDamgeAborbRate 0.9f
    if (m_isProne) {
        damage *= kProneDamgeAborbRate;
    }
    m_health -= damage;
    if (m_health <= 0) {
        if (m_isAlive) {
            fall();
        }
    }
}

void Enemy::fall()
{
}

void Enemy::die()
{
}

void Enemy::vanish()
{
}

void Enemy::prone()
{
    m_isProne = true;
    switchToFormAnimatedByKey("prone_creep");
}

void Enemy::stand()
{
    m_isProne = false;
    
    if (m_isShooting) {
        switchToFormAnimatedByKey(enemyActionKeys[kEnemyActionKeyShoot]);
    }
    else
    {
        switchToFormAnimatedByKey(enemyActionKeys[kEnemyActionKeyRun]);
    }
    
}

void Enemy::behave()
{
    if (!m_isActive || !m_isAlive) {
        return;
    }
    m_behavior->behave();
}

void Enemy::resetBehavior()
{
    m_behavior->resetBehavior();
}

void Enemy::spawnAtPosition(cocos2d::CCPoint pos)
{
    setOpacity(255);
    setPosition(pos);
    setIsAlive(true);
    setVisible(true);
    m_isShooting = false;
    m_isProne = false;
    switchToFormAnimatedByKey(enemyActionKeys[kEnemyActionKeyRun]);
}

void Enemy::addAnimationByKey(const char *key)
{
    CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName(key);
    if (animation == NULL) {
        return;
    }
    m_dictionary->setObject(animation, key);
}


void Enemy::addFlame(cocos2d::CCSpriteBatchNode *batch, const char *image)
{
    m_fireFlame = CCSprite::createWithSpriteFrameName(image);
    batch->addChild(m_fireFlame);
}

int Enemy::onBehaviorTreeActon(BTAction *action)
{
    if (action->getTag() == kEnemyActionCharge) {
        CCPoint velocity = ccp(-kEnemyDefaultSpeed, 0);
        if (m_isShooting) {
            velocity = CCPointZero;
        }
        setVelocity(velocity);
        return kBehaveSuccess;
    }
    else if (action->getTag() == kEnemyActionProne)
    {
        CCFiniteTimeAction *seq = CCSequence::create(CCDelayTime::create(EnemyProneReactionTime),
                                                     CCCallFunc::create(this, callfunc_selector(Enemy::prone)),
                                                     CCCallFunc::create(action, callfunc_selector(BTAction::actionFinished)),NULL);
        runAction(seq);
        return kBehavePending;
    }
    else if (action->getTag() == kEnemyActionStand)
    {
        stand();
        return kBehaveSuccess;
    }
    return kBehaveFailure;
}

int Enemy::onCheckCondition(BTCondition *condition)
{
    if (condition->getTag() == kEnemyCondCanCharge) {
        return kBehaveSuccess;
    }
    else if (condition->getTag() == kEnemyCondDetectDanger)
    {
        int hasDanger = false;
#define DangerDetectRange 100.0f
        
        if (m_delegate) {
            CCArray *bullets = m_delegate->getActiveBullets(this);
            for (int i=0; i<bullets->count(); i++) {
                Bullet* node = (Bullet*)bullets->objectAtIndex(i);
                if (node->getBulletType() == kBulletHostile) {
                    continue;
                }
                
                if (distanceBetweenPoints(node->getPosition(), getPosition()) < DangerDetectRange) {
                    hasDanger = true;
                    break;
                }
            }
        }
        if (hasDanger) {
            standFrameDelay = 0;
          //  CCLog("detect danger");
            return kBehaveSuccess;
        }
        return kBehaveFailure;
    }
    else if(condition->getTag() == kEnemyCondCanStandup)
    {
        if (!m_isProne) {
            return kBehaveFailure;
        }
        standFrameDelay++;
        if (standFrameDelay > kMaxChechCanStandFrame) {
            return kBehaveSuccess;
        }
    }
    return kBehaveFailure;
}

EnemyCache *EnemyCache::createWithCount(int count)
{
    EnemyCache *pRet = new EnemyCache();
    if (pRet && pRet->initWithCount(count))
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

bool EnemyCache::initWithCount(int count)
{
    if (!CCNode::init()) {
        return false;
    }
    
    m_unitCount = count;
    
    AnimationParam param;
    param.frameName = "gunman";
    param.interval = 0.1f;
    param.loops = -1;
    param.restoreFirstFrame = true;
    param.count = 8;
    
    m_unitCount = count;
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gunman01.png");
    m_batchNode = CCSpriteBatchNode::createWithTexture(frame->getTexture());
    addChild(m_batchNode);
    for (int i=0; i<m_unitCount; i++) {
        Enemy *enemy = Enemy::createWithSpriteFrameNameAndKey("gunman01.png", &param, enemyActionKeys[kEnemyActionKeyRun]);
        enemy->setTag(i);
        m_batchNode->addChild(enemy);
        enemy->setFlipX(true);
    }
    
    addForms();
    
    return true;
}

CCArray *EnemyCache::getActiveEnemy()
{
    CCArray *activeEnemies = RCUnitCache::getActiveUnits();
    return activeEnemies;
}

void EnemyCache::addForms()
{
    AnimationParam param;
    param.frameName = "gunmanfall1_";
    param.interval = 0.1f;
    param.loops = 1;
    param.restoreFirstFrame = false;
    param.count = 10;
    
    addSubFormCacheWithSpriteFrameNameAndKey("gunmanfall1_01.png", enemyActionKeys[kEnemyActionKeyFall1], &param);
    
    param.frameName = "gunmanfall2_";
    param.interval = 0.1f;
    param.loops = 1;
    param.restoreFirstFrame = false;
    param.count = 7;
    addSubFormCacheWithSpriteFrameNameAndKey("gunmanfall2_01.png", enemyActionKeys[kEnemyActionKeyFall2], &param);
    
    param.frameName = "gunmanfall3_";
    param.interval = 0.1f;
    param.loops = 1;
    param.restoreFirstFrame = false;
    param.count = 7;
    addSubFormCacheWithSpriteFrameNameAndKey("gunmanfall3_01.png", enemyActionKeys[kEnemyActionKeyFall3], &param);
    
    addEnemyProneAnimation();
    addEnemyProneCreepAnimation();
    addEnemyProneDead();
    addEenemyStandAnimation();
}

void Enemy::fireBulletAt(cocos2d::CCPoint point)
{
    CCPoint fromPos = getPosition();
}


void Enemy::shootingActionFinished(CCNode *node, void *data)
{
}

void EnemyCache::addEnemyProneAnimation()
{
    const char* prone = "prone";
    CCAnimation* animation = CCAnimation::create();
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prone_0.png");
    animation->addSpriteFrame(frame);
    animation->setDelayPerUnit(3.0f);
    animation->setLoops(1);
    animation->setRestoreOriginalFrame(false);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, prone);
    
    CCArray *enemyArray = m_batchNode->getChildren();
    for (int i=0; i<m_unitCount; i++) {
        CCObject *object = enemyArray->objectAtIndex(i);
        Enemy *enemy = dynamic_cast<Enemy*>(object);
        enemy->addAnimationByKey(prone);
    }
}

void EnemyCache::addEnemyProneCreepAnimation()
{
    const char* prone = enemyActionKeys[kEnemyActionKeyProneCreep];
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prone_0.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prone_1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prone_0.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prone_2.png"));
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(false);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, prone);
    
    CCArray *enemyArray = m_batchNode->getChildren();
    for (int i=0; i<m_unitCount; i++) {
        CCObject *object = enemyArray->objectAtIndex(i);
        Enemy *enemy = dynamic_cast<Enemy*>(object);
        enemy->addAnimationByKey(prone);
    }
}

void EnemyCache::addEnemyProneDead()
{
    const char* proneDead =  enemyActionKeys[kEnemyActionKeyProneDead];
    CCAnimation* animation = CCAnimation::create();
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prone_dead.png");
    animation->addSpriteFrame(frame);
    animation->setDelayPerUnit(3.0f);
    animation->setLoops(1);
    animation->setRestoreOriginalFrame(false);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, proneDead);
    
    CCArray *enemyArray = m_batchNode->getChildren();
    for (int i=0; i<m_unitCount; i++) {
        CCObject *object = enemyArray->objectAtIndex(i);
        Enemy *enemy = dynamic_cast<Enemy*>(object);
        enemy->addAnimationByKey(proneDead);
    }

}

void EnemyCache::addEenemyStandAnimation()
{
    const char* shoot = enemyActionKeys[kEnemyActionKeyShoot];
    CCAnimation* animation = CCAnimation::create();
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot.png");
    animation->addSpriteFrame(frame);
    animation->setDelayPerUnit(3.0f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(false);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, shoot);
    
    CCArray *enemyArray = m_batchNode->getChildren();
    for (int i=0; i<m_unitCount; i++) {
        CCObject *object = enemyArray->objectAtIndex(i);
        Enemy *enemy = dynamic_cast<Enemy*>(object);
        enemy->addAnimationByKey(shoot);
    }
}




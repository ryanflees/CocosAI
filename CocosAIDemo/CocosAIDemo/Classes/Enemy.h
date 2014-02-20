//
//  Enemy.h
//  ComicWars
//
//  Created by Bai Ryan on 13-10-13.
//
//

#ifndef __ComicWars__Enemy__
#define __ComicWars__Enemy__

#include <iostream>
#include "RCUnitCache.h"
#include "RCBehaviorTree.h"

USING_NS_AI;


enum
{
    kEnemyActionKeyRun = 0,
    kEnemyActionKeyFall1,
    kEnemyActionKeyFall2,
    kEnemyActionKeyFall3,
    kEnemyActionKeyProneCreep,
    kEnemyActionKeyProneDead,
    kEnemyActionKeyShoot
};

static const char* enemyActionKeys[]  = {
    "gunman",
    "fall1",
    "fall2",
    "fall3",
    "prone_creep",
    "prone_dead",
    "shoot"
};

typedef enum
{
    kEnemyActionCharge,
    kEnemyActionShoot,
    kEnemyActionProne,
    kEnemyActionStand,
}EnemyActionTag;

typedef enum
{
    kEnemyCondNotShooting,
    kEnemyCondPlayerInsight,
    kEnemyCondCanCharge,
    kEnemyCondCanStandup,
    kEnemyCondDetectDanger
}EnemyCondTag;


#define kProneDeadInstantlyRate 0.3f

#define kEnemyVanishTime 1.0f

class Enemy;
class EnemyDelegate
{
public:
    virtual cocos2d::CCArray* getActiveBullets(Enemy* enemy) = 0;
    virtual void onEnemyFall(Enemy* enemy) = 0;
};

class Enemy : public RCUnit
        , public BTConditionDelegate
        , public BTActionDelegate
{
public:
    
    ~Enemy();
    
    static Enemy *createWithSpriteFrameNameAndKey(const char *frameName, AnimationParam *animationParam, const char *key);
    
    virtual bool initWithSpriteFrameNameAndKey(const char *frameName,AnimationParam *animationParam, const char *key);
    
    void loseHealth(float damage);
    void fall();
    void die();
    void vanish();
    void prone();
    void stand();
    
    void behave();
    
    void resetBehavior();
    
    void spawnAtPosition(cocos2d::CCPoint pos);
    
    void fireBulletAt(cocos2d::CCPoint point);
    
    void addAnimationByKey(const char* key);
    void addFlame(cocos2d::CCSpriteBatchNode *batch, const char *image);
    
    //BTActionDelegate
    virtual int onBehaviorTreeActon(BTAction *action);
    //BTConditionDelegate
    virtual int onCheckCondition(BTCondition *condition);
private:
    cocos2d::CCSprite *m_fireFlame;
    void shootingActionFinished(CCNode *node, void *data);
    
    cocos2d::CCPoint getSpeedByPostion();
    
#define kMaxChechCanStandFrame 200
    int standFrameDelay;

    //level difficulty related
    CC_SYNTHESIZE(int, m_difficulty, Difficulty);
    CC_SYNTHESIZE(float, m_health, Health);
    CC_SYNTHESIZE(float, m_fireDelay, FireDelay);
    CC_SYNTHESIZE(float, m_sight, Sight);
    CC_SYNTHESIZE(float, m_accuracy, Accuracy);
    CC_SYNTHESIZE(float, m_bulletSpeed, BulletSpeed);
    
    CC_SYNTHESIZE(bool, m_isProne, IsProne);
    CC_SYNTHESIZE(bool, m_isShooting, IsShooting);
    
    CC_SYNTHESIZE(EnemyDelegate*, m_delegate, Delegate);
    CC_SYNTHESIZE_READONLY(BTParallel*, m_behavior, Behavior);
    
    CC_SYNTHESIZE(bool, m_isAlive,IsAlive);
    CC_SYNTHESIZE(cocos2d::CCPoint, m_velocity, Velocity);
};


class EnemyCache : public RCUnitCache
{
    
public:
    virtual bool initWithCount(int count);
    static EnemyCache *createWithCount(int count);
    
    cocos2d::CCArray *getActiveEnemy();
    
    void addEnemyProneAnimation();
    void addEnemyProneCreepAnimation();
    void addEnemyProneDead();
    void addEenemyStandAnimation();
private:
    
    cocos2d::CCSpriteBatchNode *m_fireFlameBatch;
    void addForms();
};



#endif /* defined(__ComicWars__Enemy__) */

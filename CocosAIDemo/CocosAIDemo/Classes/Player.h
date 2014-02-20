//
//  Player.h
//  ComicWars
//
//  Created by Bai Ryan on 13-10-10.
//
//

#ifndef __ComicWars__Player__
#define __ComicWars__Player__

#include "cocos2d.h"

#define kPlayerDefaultSpeed 90.0f
#define kFireTimeLimit 0.1f
#define kPlayerDefaultHealth 100

class Player;
class FireWeaponDelegate
{
public:
    virtual void fireFromPointTo(cocos2d::CCNode *node,cocos2d::CCPoint fromPos, cocos2d::CCPoint targetPos) = 0;
    virtual void onPlayerWounded(Player *player){}
    virtual void onPlayerDead(Player *player){}
};

class Player : public cocos2d::CCSprite {
    
    
public:
    Player():m_fireTimeLimit(0.0f)
    ,m_delegate(NULL)
    {}
    ~Player();
    
    virtual bool initWithSpriteFrameName(const char *frameName);
    
    static Player *createWithSpriteFrameName(const char *frameName);
    static Player  *sharedPlayer(){return m_instanceOfPlayer;}
    
    virtual bool init();
    CREATE_FUNC(Player);
    
    void fireBullteAt(cocos2d::CCPoint targetPos);
    
    void update(float dt);
    
    cocos2d::CCRect getPlayerRect();
    void loseHealth(float damage);
    
private:
    
    bool loadingMagazine;
    int bulletCount;
    float m_fireTimeLimit;
    static Player *m_instanceOfPlayer;
    
    cocos2d::CCSprite *m_arm;
    cocos2d::CCFiniteTimeAction *m_recoidAction;
    
    cocos2d::CCAnimation *m_flameAnimation;
    cocos2d::CCSprite *m_fireFlame;
    
    void onPlayFlameFinished();
    void reloadMagazine();
    void reloadFinished();
    
    void die();
    
    CC_SYNTHESIZE(float, m_health, Health);
    CC_SYNTHESIZE(bool, m_isAlive, IsAlive);
    
    CC_SYNTHESIZE(cocos2d::CCPoint, m_velocity, Velocity);

    CC_SYNTHESIZE(FireWeaponDelegate*, m_delegate, Delegate);
};

#endif /* defined(__ComicWars__Player__) */

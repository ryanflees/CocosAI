//
//  Bullets.h
//  ComicWars
//
//  Created by Bai Ryan on 13-10-16.
//
//

#ifndef __ComicWars__Bullets__
#define __ComicWars__Bullets__

#include <iostream>
#include "cocos2d.h"

#define kBulletMaxCount 100
#define kBullteFile "comicwar/bullet.png"

#define kBulletDamage 60.0f
#define kBulletDamageEnemy 15.0f

typedef enum
{
    kBulletFriendly = 1,
    kBulletHostile = 2
}BulletType;

class Bullet : public cocos2d::CCSprite {
    
    
public:
    virtual bool init();
    CREATE_FUNC(Bullet);
    
    void flyFinished();
    
    void setBulletType(int bulletType){
        m_bulletType = bulletType;
        
        if (m_bulletType == kBulletFriendly) {
            m_damage = kBulletDamage;
        }
        else if(m_bulletType == kBulletHostile)
        {
            m_damage = kBulletDamageEnemy;
        }
    }
    int getBulletType(){return m_bulletType;}
    void setIsActive(bool active){m_isActive = active;setVisible(false);}
    bool getIsActive(){return m_isActive;}
private:
    CC_SYNTHESIZE(cocos2d::CCPoint, m_velocity, Velocity);
    bool m_isActive;
    CC_SYNTHESIZE(float, m_damage, Damage);
    int m_bulletType;
};

class BulletCache : public cocos2d::CCNode
{
public:
    virtual bool init();
    
    CREATE_FUNC(BulletCache);
    
    Bullet *getNexInactiveNode();
    
    cocos2d::CCArray *getActiveBullets();
private:
    cocos2d::CCSpriteBatchNode *m_batch;
    
    
};




#endif /* defined(__ComicWars__Bullets__) */

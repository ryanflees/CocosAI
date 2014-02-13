//
//  Bullets.cpp
//  ComicWars
//
//  Created by Bai Ryan on 13-10-16.
//
//

#include "Bullet.h"

USING_NS_CC;

bool Bullet::init()
{
    if (!CCSprite::initWithFile(kBullteFile)) {
        return false;
    }
    
    setIsActive(false);
    
    return true;
}

void Bullet::flyFinished()
{
    CCLog("setIsActive false");
    setIsActive(false);
    
}

bool BulletCache::init()
{
    if (!CCNode::init()) {
        return false;
    }
    
    m_batch = CCSpriteBatchNode::create(kBullteFile, kBulletMaxCount);
    for (int i=0; i<kBulletMaxCount; i++) {
        Bullet *bullet = Bullet::create();
        m_batch->addChild(bullet);
        bullet->setColor(ccc3(255, 255, 0));
    }
    addChild(m_batch);
    return true;
}

Bullet *BulletCache::getNexInactiveNode()
{
    CCArray *bullets = m_batch->getChildren();
    CCObject *object = NULL;
    Bullet *bullet = NULL;
    CCARRAY_FOREACH(bullets, object)
    {
        bullet = dynamic_cast<Bullet*>(object);
        if (bullet->getIsActive() == false) {
            bullet->setIsActive(true);
            return bullet;
        }
    }
    return NULL;
}

CCArray *BulletCache::getActiveBullets()
{
    CCArray *activeBullets = CCArray::create();
    
    CCArray *bullets = m_batch->getChildren();
    CCObject *object = NULL;
    Bullet *bullet = NULL;
    CCARRAY_FOREACH(bullets, object)
    {
        bullet = dynamic_cast<Bullet*>(object);
        if (bullet->getIsActive() == true) {
            activeBullets->addObject(bullet);
        }
    }

    return activeBullets;
}





//
//  ComicWar.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-12.
//
//

#ifndef __CocosAIDemo__ComicWar__
#define __CocosAIDemo__ComicWar__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"

USING_NS_CC;

class BulletCache;

class ComicWar :public CCNode
        , public CCTouchDelegate
        , public FireWeaponDelegate
        , public EnemyDelegate
{
public:
    ComicWar();
    virtual ~ComicWar();
    virtual bool init();
    CREATE_FUNC(ComicWar);
    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float dt);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void fireFromPointTo(cocos2d::CCNode *node,cocos2d::CCPoint fromPos, cocos2d::CCPoint targetPos);
    
    virtual cocos2d::CCArray* getActiveBullets(Enemy* enemy);
    virtual void onEnemyFall(Enemy* enemy);
    
 private:
    void loadResource();
    void addBackground();
    void addEnemy();
    void addBullets();
    void addPlayer();
    
    void addBehaviorTreeForEnemy(Enemy* enemy);
    
    EnemyCache *m_enemyTroops;
    BulletCache *m_bullets;
    Player *m_player;
    
    bool m_touchedForFiring;
    CCPoint m_touchedForFiringPoint;
};

#endif /* defined(__CocosAIDemo__ComicWar__) */

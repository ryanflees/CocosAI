//
//  KingdomRush.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#ifndef __CocosAIDemo__KingdomRush__
#define __CocosAIDemo__KingdomRush__

#include "cocos2d.h"
#include "Archer.h"

USING_NS_CC;

class Tower;
class Bandit;
class ArrowCache;
class KingdomRush :public CCNode
,public ArcherDelegate
{
public:
    KingdomRush();
    virtual ~KingdomRush();
    virtual bool init();
    CREATE_FUNC(KingdomRush);
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    virtual CCNode* getAttackTarget(Archer* archer);
    virtual void shootAtTarget(Archer* archer, CCNode* target);
private:
    void loadResource();
    void addBackground();
    
    void addTower();
    void addBandits();
    
    Bandit* getNextInactiveBandit();
    CCArray* getActiveBandits();
    void setArcherBehavior(Bandit* bandit);
    
    CCArray* m_bandits;
    Tower* m_tower;
    ArrowCache* m_arrowCache;
};

#endif /* defined(__CocosAIDemo__KingdomRush__) */

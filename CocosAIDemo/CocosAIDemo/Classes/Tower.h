//
//  Tower.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#ifndef __CocosAIDemo__Tower__
#define __CocosAIDemo__Tower__

#include "cocos2d.h"

USING_NS_CC;

#define ARCHER_COUNT_IN_TOWER 2

class Archer;
class ArcherDelegate;
class Tower :public CCNode
{
public:
    Tower();
    virtual ~Tower();
    virtual bool init();
    CREATE_FUNC(Tower);
    virtual void onEnter();
    virtual void onExit();

    void setArcherBehavior(ArcherDelegate* delegate);
private:
    void addTower();
    void addArcher();
    Archer* m_archers[ARCHER_COUNT_IN_TOWER];
};

#endif /* defined(__CocosAIDemo__Tower__) */

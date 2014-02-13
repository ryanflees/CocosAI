//
//  BTNode.h
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#ifndef __CocosAI__BTNode__
#define __CocosAI__BTNode__

#include "cocos2d.h"

namespace CocosAI {

class BTNode :public cocos2d::CCNode
{
public:
    BTNode();
    virtual ~BTNode();
    virtual bool init();
    CREATE_FUNC(BTNode);
    virtual void addBTNode(BTNode *node);
    virtual int behave();
    virtual void actionFinished();
    virtual void resetBehavior();
protected:
    int m_behaviorStatus;
    cocos2d::CCArray *m_btChildren;
};

}

#endif /* defined(__CocosAI__BTNode__) */

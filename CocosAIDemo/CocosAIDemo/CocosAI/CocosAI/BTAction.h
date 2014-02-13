//
//  BTAction.h
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#ifndef __CocosAI__BTAction__
#define __CocosAI__BTAction__

#include "cocos2d.h"
#include "BTNode.h"

USING_NS_CC;

namespace CocosAI {

class BTAction;
class BTActionDelegate
{
public:
	virtual int onBehaviorTreeActon(BTAction* action) = 0;
};

class BTAction :public BTNode
{
public:
    BTAction();
    virtual ~BTAction();
    virtual bool init();
    CREATE_FUNC(BTAction);
    virtual int behave(void);
    virtual void actionFinished(void);
private:
	CC_SYNTHESIZE(BTActionDelegate*, m_delegate, Delegate);
};
    
}

#endif /* defined(__CocosAI__BTAction__) */

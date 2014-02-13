//
//  BTCondition.h
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#ifndef __CocosAI__BTCondition__
#define __CocosAI__BTCondition__

#include "cocos2d.h"
#include "BTNode.h"

USING_NS_CC;

namespace CocosAI {

class BTCondition;
class BTConditionDelegate
{
public:
    virtual int onCheckCondition(BTCondition *condition) = 0;
};

class BTCondition :public BTNode
{
public:
    BTCondition();
    virtual ~BTCondition();
    virtual bool init();
    CREATE_FUNC(BTCondition);
    
    virtual int behave();
private:
    CC_SYNTHESIZE(BTConditionDelegate*, m_delegate, Delegate);
};
    
}

#endif /* defined(__CocosAI__BTCondition__) */

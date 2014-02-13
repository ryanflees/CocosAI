//
//  BTParallel.cpp
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#include "BTParallel.h"
#include "RCBehaviorTree.h"

namespace CocosAI {

BTParallel::BTParallel()
{

}

BTParallel::~BTParallel()
{

}

bool BTParallel::init()
{
    if (!BTNode::init())
    {
        return false;
    }
    return true;
}

int BTParallel::behave()
{
    if (BTNode::behave() == kBehaveFailure)
	{
        return kBehaveFailure;
    }
    
    int result = kBehaveFailure;
    
    CCObject *object;
    CCARRAY_FOREACH(m_btChildren, object)
    {
        BTNode *node = dynamic_cast<BTNode*>(object);
        if(node->behave() == kBehaveSuccess)
        {
            result = kBehaveSuccess;
        }
    }
    return result;
}

}

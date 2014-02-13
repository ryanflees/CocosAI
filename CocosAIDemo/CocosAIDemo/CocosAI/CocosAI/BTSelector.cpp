//
//  BTSelector.cpp
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#include "BTSelector.h"
#include "RCBehaviorTree.h"

namespace CocosAI {

BTSelector::BTSelector()
{

}

BTSelector::~BTSelector()
{

}

bool BTSelector::init()
{
    if (!BTNode::init())
    {
        return false;
    }
    return true;
}

int BTSelector::behave()
{
    if (BTNode::behave() == kBehaveFailure) {
        return kBehaveFailure;
    }
    if (m_behaviorStatus == kBehaveRunning) {
        return kBehavePending;
    }
    else if(m_behaviorStatus == kBehaveReady)
    {
        CCObject *object;
        CCARRAY_FOREACH(m_btChildren, object)
        {
            BTNode *node = dynamic_cast<BTNode*>(object);
            int result = node->behave();
            
            if(result == kBehaveSuccess)
            {
                return kBehaveSuccess;
            }
            else if(result == kBehavePending)
            {
                m_behaviorStatus = kBehaveRunning;
                return kBehavePending;
            }
        }
    }
    
    return kBehaveFailure;
}

}



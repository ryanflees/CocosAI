//
//  BTSequence.cpp
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#include "BTSequence.h"
#include "RCBehaviorTree.h"

USING_NS_AI;

BTSequence::BTSequence()
{

}

BTSequence::~BTSequence()
{

}

bool BTSequence::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    return true;
}

int BTSequence::behave()
{
    if (BTNode::behave() == kBehaveFailure)
	{
        return kBehaveFailure;
    }
    
    if(m_behaviorStatus == kBehaveRunning)
    {
        return kBehavePending;
    }
    else if (m_behaviorStatus == kBehaveReady)
    {
        CCObject *object;
        CCARRAY_FOREACH(m_btChildren, object)
        {
            BTNode *node = dynamic_cast<BTNode*>(object);
            
            int result = node->behave();
            if(result == kBehaveFailure)
            {
                return kBehaveFailure;
            }
            else if(result == kBehavePending)
            {
                m_behaviorStatus = kBehaveRunning;
                return kBehavePending;
            }
        }
        return kBehaveSuccess;
    }
    return kBehaveFailure;
}

void BTSequence::actionFinished( )
{
    m_behaviorStatus = kBehaveReady;
    
    BTSequence *sequence = dynamic_cast<BTSequence*>(getParent());
    if (sequence != NULL)
	{
        sequence->actionFinished();
    }
}


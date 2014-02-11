//
//  BTAction.cpp
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#include "BTAction.h"
#include "RCBehaviorTree.h"
#include "BTSequence.h"

USING_NS_AI;

BTAction::BTAction():m_delegate(NULL)
{

}

BTAction::~BTAction()
{

}

bool BTAction::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    return true;
}

int BTAction::behave()
{
	if (m_delegate == NULL)
	{
		return kBehaveFailure;
	}
	else
	{
		int result = m_delegate->onBehaviorTreeActon(this);
		if (result == kBehaveSuccess)
		{
			return kBehaveSuccess;
		}
		else if (result == kBehavePending)
		{
			return kBehavePending;
		}
		else
		{
			return kBehaveFailure;
		}
	}
}

void BTAction::actionFinished()
{
    m_behaviorStatus = kBehaveReady;
    BTSequence *sequence = dynamic_cast<BTSequence*>(getParent());
    if (sequence != NULL)
	{
        sequence->actionFinished();
    }
}

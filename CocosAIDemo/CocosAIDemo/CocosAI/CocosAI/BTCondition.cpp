//
//  BTCondition.cpp
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#include "BTCondition.h"
#include "RCBehaviorTree.h"

namespace CocosAI {

BTCondition::BTCondition():m_delegate()
{

}

BTCondition::~BTCondition()
{

}

bool BTCondition::init()
{
    if (!BTNode::init())
    {
        return false;
    }
    return true;
}

int BTCondition::behave()
{
    if (m_delegate) {
        return m_delegate->onCheckCondition(this);
    }
    return kBehaveFailure;
}
    
}
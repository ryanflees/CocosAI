//
//  BTNode.cpp
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#include "BTNode.h"
#include "RCBehaviorTree.h"

USING_NS_CC;

namespace CocosAI {

BTNode::BTNode():m_btChildren()
,m_behaviorStatus(kBehaveReady)
{

}

BTNode::~BTNode()
{
    CC_SAFE_RELEASE(m_btChildren);
}

bool BTNode::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    m_btChildren = CCArray::create();
    m_btChildren->retain();
    
    return true;
}

void BTNode::addBTNode(BTNode *node)
{
    addChild(node);
    m_btChildren->addObject(node);
}

int BTNode::behave()
{
    return kBehaveSuccess;
}

void BTNode::actionFinished()
{
    m_behaviorStatus = kBehaveReady;
}

void BTNode::resetBehavior()
{
    m_behaviorStatus = kBehaveReady;
    
    for (int i=0; i<m_btChildren->count(); i++) {
        BTNode *node = (BTNode*)m_btChildren->objectAtIndex(i);
        node->resetBehavior();
    }
}
    
}

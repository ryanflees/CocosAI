//
//  ArrowTest.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-19.
//
//

#include "ArrowTest.h"
#include "Arrow.h"

ArrowTest::ArrowTest()
{

}

ArrowTest::~ArrowTest()
{

}

bool ArrowTest::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create(ccc4(255, 255, 255, 255), screenSize.width, screenSize.height);
    addChild(layer);

    m_arrow = Arrow::create();
    addChild(m_arrow);
    
    CCPoint startPoint = ccp(500,600);
    CCPoint endPoint = ccp(500,500);
    float shootHeight = 100;
    
    CCJumpTo* jump = CCJumpTo::create(0.5f, endPoint, shootHeight, 1);
    m_arrow->spawnAtPosition(startPoint);
    CCCallFuncN* callback = CCCallFuncN::create(m_arrow, callfuncN_selector(Arrow::shootEnd));
    CCFiniteTimeAction* seq = CCSequence::create(jump, CCDelayTime::create(0.4f), callback, NULL);
    m_arrow->runAction(seq);

    return true;
}

void ArrowTest::onEnter()
{
    
    CCNode::onEnter();
}

void ArrowTest::onExit()
{
    CCNode::onExit();
}

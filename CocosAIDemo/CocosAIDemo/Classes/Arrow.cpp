//
//  Arrow.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-18.
//
//

#include "Arrow.h"
#include "MathFuncion.h"
#include <math.h>

#define kArrowSpeed 100

Arrow::Arrow():m_active()
,m_jumpTo()
{

}

Arrow::~Arrow()
{

}

bool Arrow::init()
{
    if (!CCSprite::initWithFile(kTowerArrowImage)) {
        return false;
    }
    
    m_trailFunction = MathFuncion::create();
    m_trailFunction->retain();
    
    return true;
}

void Arrow::onEnter()
{
    CCNode::onEnter();
    scheduleUpdate();
}

void Arrow::onExit()
{
    CCNode::onExit();
    unscheduleUpdate();
}

void Arrow::update(float dt)
{
    if (m_active) {
        
#if kArrowUseMathFunction
        if (m_endPoint.x > m_startPoint.y) {
            if (getPosition().x >= m_endPoint.x) {
                shootEnd(this);
            }
            else
            {
                float xPosition = getPosition().x + kArrowSpeed*dt;
                float yPosition = m_trailFunction->caculate(xPosition);
                setPosition(ccp(xPosition, yPosition));
            }
        }
        else
        {
            if (getPosition().x <= m_endPoint.x) {
                shootEnd(this);
            }
            else
            {
                float xPosition = getPosition().x - kArrowSpeed*dt;
                float yPosition = m_trailFunction->caculate(xPosition);
                setPosition(ccp(xPosition, yPosition));
            }
        }
#else
        
        if (m_jumpTo) {
            CCPoint delta = m_jumpTo->getDelta();
            CCLOG("delta %f %f",delta.x ,delta.y);
            
            if (delta.x >0 && delta.y >= 0) {
                float angle = atan(delta.y/delta.x);
                angle = radtodeg(angle);
                setRotation(90-angle);
            }
            else if (delta.x < 0 && delta.y >= 0)
            {
                float angle = atan(delta.y/delta.x);
                angle = radtodeg(angle);
                setRotation(180+angle);
            }
            else if (delta.x >0 && delta.y <0)
            {
                float angle = atan(delta.y/delta.x);
                angle = radtodeg(angle);
                setRotation(-angle);
            }
            else if (delta.x <0 && delta.y <0)
            {
                float angle = atan(delta.y/delta.x);
                angle = radtodeg(angle);
                setRotation(180-angle);
            }
            else
            {
                if (delta.y <= 0) {
                    setRotation(90);
                }
                else
                {
                    setRotation(-90);
                }
            }
        }
#endif
    }
}

void Arrow::spawnAtPosition(const CCPoint& point)
{
    setPosition(point);
    setVisible(true);
    m_active = true;
}

void Arrow::shootEnd(CCNode* node)
{
    m_jumpTo = NULL;
    setVisible(false);
    m_active = false;
}


void Arrow::spawn(const CCPoint& startPoint, const CCPoint& endPoint, float height)
{
    m_startPoint = startPoint;
    m_endPoint = endPoint;

    //    float x1 = startPoint.x;
//    float y1 = startPoint.y;
//    float x2 = endPoint.x;
//    float y2 = endPoint.y;
//    
//    float higherY = (y1 > y2)?y1:y2;
//    float y0 = higherY + height;
//    
//    float c = y0;
//    
//    float param = sqrt((y1-y0)/(y2-y0));
//    float b1 = (x1 -param*x2)/(param -1);
//    float b2 = -(param*x2 + x1)/(param +1);
//    float A1 = (y1 - y0)/((x1 + b1) * (x1 + b1));
//    float A2 = (y1 - y0)/((x1 + b2) * (x2 + b2));
//    float A;
//    float b;
//    if (A1 <0) {
//        A = A1;
//        b = b1;
//    }
//    else if (A2 <0) {
//        A = A2;
//        b = b2;
//    }
//    else
//    {
//        CCAssert(NULL, "both A1 A2 is positive");
//    }
//    CCString *functionString = CCString::createWithFormat("%f*($x + (%f))*($x + (%f)) + %f",A,b,b,c);
//    m_trailFunction->setFunction(functionString->getCString());
//
    
    float x1 = startPoint.x;
    float y1 = startPoint.y;
    float x2 = endPoint.x;
    float y2 = endPoint.y;

    float alpha;
    
    if (x1 == x2)
    {
        x1 += 1;
        m_startPoint.x +=1;
    }
    if (x2 > x1 && y2 >= y1) {
        alpha = pi/2 - (pi/2 - atan((y2-y1)/(x2-x1)))/2;
    }
    else if (x2 < x1 && y2 >= y1)
    {
        alpha = pi/2 + (atan((y2-y1)/(x2-x1)) + pi/2)/2;
    }
    else if (x2 < x1 && y2 <= y1)
    {
        alpha = pi/2 + (pi - atan((x2-x1)/(y2-y1)))/2;
    }
    else if (x2 > x1 && y2 <= y1)
    {
        alpha = pi/2 - (pi + atan((y2-y1)/(x2-x1)))/2;
    }
    alpha = radtodeg(alpha);
    CCLog("aplah %f" , alpha);
    if (alpha < 70 && alpha > 0) {
        alpha = 70;
    }
    if (alpha > 110 && alpha < 180) {
        alpha = 110;
    }
    float slope = tan(degtorad(alpha));
    float a = (slope*(x1-x2)-y1+y2)/((x1-x2)*(x1-x2));
    float b = slope - 2*a*x1;
    float c = y1 - a*x1*x1 - b*x1;
    CCString *functionString = CCString::createWithFormat("(%f)*($x)*($x) + (%f)*($x) + %f",a,b,c);
    m_trailFunction->setFunction(functionString->getCString());
    
    float startPointSope = 2*a*x1 +b;
    float angeStart = radtodeg(atan(startPointSope));
    CCLOG("startPointSope %f angle %f",startPointSope, angeStart);
    
    float endPointSlope = 2*a*x2 + b;
    float angle = atan(endPointSlope);
    angle = radtodeg(angle);
    CCLOG("endPointSlope %f angle %f",endPointSlope, angle);
    float testStartY = m_trailFunction->caculate(m_startPoint.x);
    float testEndY = m_trailFunction->caculate(m_endPoint.x);
    CCLog("startPoint: %f %f", m_startPoint.x, testStartY);
    CCLog("endPoint: %f %f", m_endPoint.x, testEndY);
    
    setPosition(startPoint);
    //setPosition(CCPointZero);
    setVisible(true);
    m_active = true;
    
}

void Arrow::draw()
{
    CCSprite::draw();
    if (!m_trailFunction) {
        return;
    }
    ccPointSize(1);
    ccDrawColor4B(0, 0, 0, 255);
    float widthRange = m_endPoint.x - m_startPoint.x;
    for (int i=0; i<1000; i++) {
        float step = widthRange*i/1000;
        float cursorPointX = m_startPoint.x + step;
        float cursorPointY = m_trailFunction->caculate(cursorPointX);
        ccDrawPoint(ccp(cursorPointX, cursorPointY));
    }
}

ArrowCache::ArrowCache()
{
    
}

ArrowCache::~ArrowCache()
{

}

bool ArrowCache::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    m_batchNode = CCSpriteBatchNode::create(kTowerArrowImage);
    addChild(m_batchNode);
    
    for (int i=0; i<kTowerArrowCount; i++) {
        Arrow* arrow = Arrow::create();
        m_batchNode->addChild(arrow);
        arrow->setVisible(false);
    }
    
    return true;
}

void ArrowCache::onEnter()
{
    
    CCNode::onEnter();
}

void ArrowCache::onExit()
{
    CCNode::onExit();
}

Arrow* ArrowCache::getNextInactiveNode()
{
    CCObject* object;
    CCARRAY_FOREACH(m_batchNode->getChildren(), object)
    {
        Arrow* arrow = (Arrow*)object;
        if (!arrow->getIsActive()) {
            return arrow;
        }
    }
    return NULL;
}


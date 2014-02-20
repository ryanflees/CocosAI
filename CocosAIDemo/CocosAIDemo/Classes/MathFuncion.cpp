//
//  MathFuncion.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-19.
//
//

#include "MathFuncion.h"
#include "RCStringHelper.h"

MathFuncion::MathFuncion()
{

}

MathFuncion::~MathFuncion()
{
    delete m_mathParser;
}

bool MathFuncion::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    m_mathParser = new ZExpParser();
    
    return true;
}

void MathFuncion::onEnter()
{
    
    CCNode::onEnter();
}

void MathFuncion::onExit()
{
    CCNode::onExit();
}

void MathFuncion::setFunction(const char *functionString)
{
    m_function = functionString;
}

double MathFuncion::caculate(double x)
{
    int length = strlen(m_function.c_str());
    if (length <= 1) {
        return 0;
    }
    CCString *xString = CCString::createWithFormat("%f",x);
    CCString *expression = RCStringHelper::sharedStringHelper()->stringByReplacingOccurrencesOfString(m_function.c_str(), "$x", xString->getCString());
    return m_mathParser->Evaluate(expression->getCString());
}

double MathFuncion::caculate(double x, double y)
{
    CCString *xString = CCString::createWithFormat("%f",x);
    CCString *yString = CCString::createWithFormat("%f",y);
    CCString *expression = RCStringHelper::sharedStringHelper()->stringByReplacingOccurrencesOfString(m_function.c_str(), "$x", xString->getCString());
    expression = RCStringHelper::sharedStringHelper()->stringByReplacingOccurrencesOfString(expression->getCString(), "$y", yString->getCString());
    
    return m_mathParser->Evaluate(expression->getCString());
}

double MathFuncion::caculate(double x, double y, double z)
{
    CCString *xString = CCString::createWithFormat("%f",x);
    CCString *yString = CCString::createWithFormat("%f",y);
    CCString *zString = CCString::createWithFormat("%f",z);
    CCString *expression = RCStringHelper::sharedStringHelper()->stringByReplacingOccurrencesOfString(m_function.c_str(), "$x", xString->getCString());
    expression = RCStringHelper::sharedStringHelper()->stringByReplacingOccurrencesOfString(expression->getCString(), "$y", yString->getCString());
    expression = RCStringHelper::sharedStringHelper()->stringByReplacingOccurrencesOfString(expression->getCString(), "$z", zString->getCString());
    return m_mathParser->Evaluate(expression->getCString());
}

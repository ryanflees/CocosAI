//
//  MathFuncion.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-19.
//
//

#ifndef __CocosAIDemo__MathFuncion__
#define __CocosAIDemo__MathFuncion__

#include "cocos2d.h"
#include <string.h>
#include "ZExpParser.h"

using namespace std;
USING_NS_CC;

class MathFuncion :public CCNode
{
public:
    MathFuncion();
    virtual ~MathFuncion();
    virtual bool init();
    CREATE_FUNC(MathFuncion);
    virtual void onEnter();
    virtual void onExit();
    
    void setFunction(const char* functionString);
    double caculate(double x);
    double caculate(double x, double y);
    double caculate(double x, double y, double z);
    
private:
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, m_function, Function);
    ZExpParser* m_mathParser;
};

#endif /* defined(__CocosAIDemo__MathFuncion__) */

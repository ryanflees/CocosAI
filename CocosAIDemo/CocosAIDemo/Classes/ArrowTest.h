//
//  ArrowTest.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-19.
//
//

#ifndef __CocosAIDemo__ArrowTest__
#define __CocosAIDemo__ArrowTest__

#include "cocos2d.h"

USING_NS_CC;

class Arrow;
class ArrowTest :public CCNode
{
public:
    ArrowTest();
    virtual ~ArrowTest();
    virtual bool init();
    CREATE_FUNC(ArrowTest);
    virtual void onEnter();
    virtual void onExit();
private:
    Arrow* m_arrow;
};

#endif /* defined(__CocosAIDemo__ArrowTest__) */

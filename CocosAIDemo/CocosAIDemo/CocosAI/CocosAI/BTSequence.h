//
//  BTSequence.h
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#ifndef __CocosAI__BTSequence__
#define __CocosAI__BTSequence__

#include "cocos2d.h"
#include "BTNode.h"

USING_NS_CC;

namespace CocosAI {

class BTSequence :public BTNode
{
public:
    BTSequence();
    virtual ~BTSequence();
    virtual bool init();
    CREATE_FUNC(BTSequence);
    virtual int behave();
    virtual void actionFinished();
};
    
}

#endif /* defined(__CocosAI__BTSequence__) */

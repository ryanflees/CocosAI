//
//  BTParallel.h
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#ifndef __CocosAI__BTParallel__
#define __CocosAI__BTParallel__

#include "cocos2d.h"
#include "BTNode.h"

USING_NS_CC;

namespace CocosAI {

class BTParallel :public BTNode
{
public:
    BTParallel();
    virtual ~BTParallel();
    virtual bool init();
    CREATE_FUNC(BTParallel);
    virtual int behave(void);
};

}

#endif /* defined(__CocosAI__BTParallel__) */

//
//  BTSelector.h
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#ifndef __CocosAI__BTSelector__
#define __CocosAI__BTSelector__

#include "cocos2d.h"
#include "BTNode.h"

USING_NS_CC;

namespace CocosAI {

class BTSelector :public BTNode
{
public:
    BTSelector();
    virtual ~BTSelector();
    virtual bool init();
    CREATE_FUNC(BTSelector);
    virtual int behave();
};
    
}

#endif /* defined(__CocosAI__BTSelector__) */

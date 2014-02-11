//
//  RCBehaviorTree.h
//  CocosAI
//
//  Created by Bai Ryan on 14-2-11.
//  Copyright (c) 2014年 Bai Ryan. All rights reserved.
//

#ifndef CocosAI_RCBehaviorTree_h
#define CocosAI_RCBehaviorTree_h

#define USING_NS_AI using namespace CocosAI;

namespace CocosAI {
    
    typedef enum
    {
        kBehaveReady = 0,
        kBehaveRunning = 1
    }BehaveStatus;
    
    typedef enum
    {
        kBehaveSuccess = 0,
        kBehavePending = 1,
        kBehaveFailure = 2
    }BehaveResult;
    
}

#endif

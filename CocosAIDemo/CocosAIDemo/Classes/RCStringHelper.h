//
//  RCStringHelper.h
//  TilemapDemo
//
//  Created by hy on 12/31/13.
//
//

#ifndef __TilemapDemo__RCStringHelper__
#define __TilemapDemo__RCStringHelper__

#include <iostream>
#include "cocos2d.h"

class RCStringHelper : cocos2d::CCNode {
    
public:
    static RCStringHelper* sharedStringHelper();
    static void purge();
    static RCStringHelper* m_instanceOfStringHelper;
    
    virtual bool init();
    CREATE_FUNC(RCStringHelper);
    
    cocos2d::CCString *stringByDeletingLastPathComponent(const char *cstring);
    cocos2d::CCString *stringByAppendingPathComponent(const char *cstring, const char *appendingCString);
    cocos2d::CCString *stringByReplacingOccurrencesOfString(const char* cstring, const char* replaceCString, const char* withCString);
};

#endif /* defined(__TilemapDemo__RCStringHelper__) */

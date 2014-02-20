//
//  RCStringHelper.cpp
//  TilemapDemo
//
//  Created by hy on 12/31/13.
//
//

#include "RCStringHelper.h"

USING_NS_CC;

RCStringHelper* RCStringHelper::sharedStringHelper()
{
    if (!m_instanceOfStringHelper) {
        m_instanceOfStringHelper = RCStringHelper::create();
        m_instanceOfStringHelper->retain();
    }
    return m_instanceOfStringHelper;
}

void RCStringHelper::purge()
{
    CC_SAFE_RELEASE(m_instanceOfStringHelper);
}

RCStringHelper* RCStringHelper::m_instanceOfStringHelper = NULL;

bool RCStringHelper::init()
{
    if (!CCNode::init()) {
        return false;
    }
    
    return true;
}

CCString *RCStringHelper::stringByDeletingLastPathComponent(const char *cstring)
{
    NSString *oldString = [NSString stringWithUTF8String:cstring];
    NSString *newString = [oldString stringByDeletingLastPathComponent];
    return CCString::create([newString UTF8String]);
}

CCString *RCStringHelper::stringByAppendingPathComponent(const char *cstring, const char *appendingCString)
{
    NSString *oldString = [NSString stringWithUTF8String:cstring];
    NSString *appendingString = [NSString stringWithUTF8String:appendingCString];
    NSString *newString = [oldString stringByAppendingPathComponent:appendingString];
    return CCString::create([newString UTF8String]);
}


CCString *RCStringHelper::stringByReplacingOccurrencesOfString(const char* cstring, const char* replaceCString, const char* withCString)
{
    NSString *oldString = [NSString stringWithUTF8String:cstring];
    NSString *replaceString = [NSString stringWithUTF8String:replaceCString];
    NSString *withString = [NSString stringWithUTF8String:withCString];
    NSString *newString = [oldString stringByReplacingOccurrencesOfString:replaceString withString:withString];
    return CCString::create(newString.UTF8String);
}





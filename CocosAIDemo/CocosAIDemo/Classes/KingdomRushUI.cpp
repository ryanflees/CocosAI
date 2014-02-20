//
//  KingdomRushUI.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-14.
//
//

#include "KingdomRushUI.h"
#include "SceneManager.h"

KingdomRushUI::KingdomRushUI()
{

}

KingdomRushUI::~KingdomRushUI()
{

}

bool KingdomRushUI::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    return true;
}
void KingdomRushUI::onEnter()
{
    CCNode::onEnter();
}

void KingdomRushUI::onExit()
{
    CCNode::onExit();
}

SEL_MenuHandler KingdomRushUI::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "NAME", KingdomRushUI::FUNCTION);
    return NULL;
}

SEL_CCControlHandler KingdomRushUI::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked", KingdomRushUI::onButtonClicked);
    return NULL;
}

bool KingdomRushUI::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NAME", TYPE,VALUE);
    return false;
}

bool KingdomRushUI::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    return false;
}


void KingdomRushUI::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    
    
}

void KingdomRushUI::onButtonClicked(CCObject* object)
{
    SceneManager::sharedSceneManager()->returnMainMenu();
}

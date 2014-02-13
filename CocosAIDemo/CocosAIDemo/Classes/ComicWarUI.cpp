//
//  ComicWarUI.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-12.
//
//

#include "ComicWarUI.h"
#include "SceneManager.h"

ComicWarUI::ComicWarUI():m_returnButton()
{

}

ComicWarUI::~ComicWarUI()
{
}

bool ComicWarUI::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    return true;
}
void ComicWarUI::onEnter()
{
    CCNode::onEnter();
}

void ComicWarUI::onExit()
{
    CCNode::onExit();
}

SEL_MenuHandler ComicWarUI::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "NAME", ComicWarUI::FUNCTION);
    return NULL;
}

SEL_CCControlHandler ComicWarUI::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked", ComicWarUI::onButtonClicked);
    return NULL;
}

bool ComicWarUI::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "returnButton", CCControlButton* ,m_returnButton);
    return false;
}

bool ComicWarUI::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    return false;
}


void ComicWarUI::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    if (m_returnButton) {
        m_returnButton->setTouchPriority(-1);
    }
}

void ComicWarUI::onButtonClicked(CCObject *object)
{
    SceneManager::sharedSceneManager()->returnMainMenu();
}

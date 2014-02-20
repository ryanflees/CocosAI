//
//  MainMenu.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-12.
//
//

#include "MainMenu.h"
#include "SceneManager.h"
#include "ArrowTest.h"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

bool MainMenu::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    return true;
}
void MainMenu::onEnter()
{
    CCLayer::onEnter();
}
void MainMenu::onExit()
{
    CCLayer::onExit();
}

SEL_MenuHandler MainMenu::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "NAME", MainMenu::FUNCTION);
    return NULL;
}

SEL_CCControlHandler MainMenu::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked", MainMenu::onButtonClicked);
    return NULL;
}

bool MainMenu::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NAME", TYPE,VALUE);
    return false;
}

bool MainMenu::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    return false;
}

void MainMenu::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    
    
}

void MainMenu::onButtonClicked(CCObject* object)
{
    CCNode *node = (CCNode*)object;
    if (node->getTag() == 1) {
        SceneManager::sharedSceneManager()->switchToComicWar();
    }
    else if (node->getTag() == 2)
    {
        SceneManager::sharedSceneManager()->switchToKingdomRush();
    }
    else if (node->getTag() == 3)
    {
        CCScene *scene = CCScene::create();
        ArrowTest *node = ArrowTest::create();
        scene->addChild(node);
        CCDirector::sharedDirector()->pushScene(scene);
    }
}

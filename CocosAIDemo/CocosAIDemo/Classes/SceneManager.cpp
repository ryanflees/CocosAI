//
//  SceneManager.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-12.
//
//

#include "SceneManager.h"
#include "MainMenu.h"
#include "ComicWar.h"
#include "ComicWarUI.h"

SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
    
}

SceneManager* SceneManager::m_instanceOfSceneManager = NULL;

SceneManager* SceneManager::sharedSceneManager()
{
    if (!m_instanceOfSceneManager)
    {
        m_instanceOfSceneManager = new SceneManager();
    }
    return m_instanceOfSceneManager;
}

void SceneManager::purge()
{
    if (m_instanceOfSceneManager) {
        delete (m_instanceOfSceneManager);
    }
}

void SceneManager::showMainMenu()
{
    CCScene *pScene = CCScene::create();
    CCNodeLoaderLibrary *pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCBReader *ccbReader = new CCBReader(pLoaderLibrary);
    registerCustomControlsForNodeloader(pLoaderLibrary);
    pLoaderLibrary->registerCCNodeLoader("MainMenu", MainMenuLoader::loader());
    
    CCNode *pNode = ccbReader->readNodeGraphFromFile("ccbi/main_menu.ccbi");
    ccbReader->release();
    pScene->addChild(pNode);
    CCDirector::sharedDirector()->runWithScene(pScene);
}

void SceneManager::returnMainMenu()
{
    CCDirector::sharedDirector()->popScene();
}

void SceneManager::switchToComicWar()
{
    CCScene *pScene = CCScene::create();
    ComicWar *node = ComicWar::create();
    pScene->addChild(node);
    
    CCNodeLoaderLibrary *pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCBReader *ccbReader = new CCBReader(pLoaderLibrary);
    registerCustomControlsForNodeloader(pLoaderLibrary);
    pLoaderLibrary->registerCCNodeLoader("ComicWarUI", ComicWarUILoader::loader());
    CCNode *comicWarUI = ccbReader->readNodeGraphFromFile("ccbi/comic_war_ui.ccbi");
    ccbReader->release();
    node->addChild(comicWarUI,5);
    
    CCDirector::sharedDirector()->pushScene(pScene);
}

void SceneManager::registerCustomControlsForNodeloader(CCNodeLoaderLibrary *pLoaderLibrary)
{
}

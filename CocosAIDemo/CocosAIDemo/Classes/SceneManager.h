//
//  SceneManager.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-12.
//
//

#ifndef __CocosAIDemo__SceneManager__
#define __CocosAIDemo__SceneManager__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();
    
    static SceneManager* m_instanceOfSceneManager;
    static SceneManager* sharedSceneManager();
    static void purge();
    
    void showMainMenu();
    void returnMainMenu();
    void switchToComicWar();
    void registerCustomControlsForNodeloader(CCNodeLoaderLibrary *pLoaderLibrary);
private:
    
};

#endif /* defined(__CocosAIDemo__SceneManager__) */

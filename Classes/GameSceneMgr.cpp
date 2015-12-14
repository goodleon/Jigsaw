//
//  GameSceneMgr.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-24.
//
//

#include "GameSceneMgr.h"
#include "cocos2d.h"
#include "StartLayer.h"
#include "PlayMain.h"
#include "ThanksLayer.h"
#include "ChooseLayer.h"

USING_NS_CC;

void GameSceneMgr::replace(SceneType scene)
{
    m_curScene = scene;
    
    Scene* to_scene = nullptr;
    switch (m_curScene)
    {
        case kStartScene:
        {
            to_scene = StartLayer::createScene();
        }
            break;
        case kThanksScene:
        {
            to_scene = ThanksLayer::createScene();
        }
            break;
//        case kHistoryScene:
//        {
//            to_scene = HistoryLayer::createScene();
//        }
//            break;
        case kChooseScene:
        {
            to_scene = ChooseLayer::createScene();
        }
            break;
        case kPlayScene:
        {
            to_scene = PlayMain::createScene();
        }
            break;
        default:
            break;
    }
    
    assert(to_scene);
    Director::getInstance()->replaceScene(to_scene);
}

JigScene* GameSceneMgr::curScene()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    return static_cast<JigScene*>(scene);
}
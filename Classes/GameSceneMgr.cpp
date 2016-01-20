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

TransitionScene* random_transition(Scene* scene)
{
    const float use_time = 1.0f;

    int idx = random(0,25);

    if (idx==0) {
        return TransitionFadeDown::create(use_time, scene);
    }
    else if (idx==1) {
        return TransitionRotoZoom::create(use_time, scene);
    }
    else if (idx==2) {
        return TransitionJumpZoom::create(use_time, scene);
    }
    else if (idx==3) {
        return TransitionMoveInL::create(use_time, scene);
    }
    else if (idx==4) {
        return TransitionMoveInR::create(use_time, scene);
    }
    else if (idx==5) {
        return TransitionMoveInT::create(use_time, scene);
    }
    else if (idx==6) {
        return TransitionMoveInB::create(use_time, scene);
    }
    else if (idx==7) {
        return TransitionSlideInL::create(use_time, scene);
    }
    else if (idx==8) {
        return TransitionSlideInR::create(use_time, scene);
    }
    else if (idx==9) {
        return TransitionSlideInB::create(use_time, scene);
    }
    else if (idx==10) {
        return TransitionSlideInT::create(use_time, scene);
    }
    else if (idx==11) {
        return TransitionShrinkGrow::create(use_time, scene);
    }
    else if (idx==12) {
        return TransitionFlipX::create(use_time, scene);
    }
    else if (idx==13) {
        return TransitionFlipY::create(use_time, scene);
    }
    else if (idx==14) {
        return TransitionFlipAngular::create(use_time, scene);
    }
    else if (idx==15) {
        return TransitionZoomFlipX::create(use_time, scene);
    }
    else if (idx==16) {
        return TransitionZoomFlipY::create(use_time, scene);
    }
    else if (idx==17) {
        return TransitionZoomFlipAngular::create(use_time, scene);
    }
    else if (idx==18) {
        return TransitionFade::create(use_time, scene);
    }
    else if (idx==19) {
        return TransitionCrossFade::create(use_time, scene);
    }
    else if (idx==20) {
        return TransitionTurnOffTiles::create(use_time, scene);
    }
    else if (idx==21) {
        return TransitionSplitCols::create(use_time, scene);
    }
    else if (idx==22) {
        return TransitionSplitRows::create(use_time, scene);
    }
    else if (idx==23) {
        return TransitionFadeTR::create(use_time, scene);
    }
    else if (idx==24) {
        return TransitionFadeBL::create(use_time, scene);
    }
    else if (idx==25) {
        return TransitionFadeUp::create(use_time, scene);
    }
    assert(false);
}

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

    Director::getInstance()->replaceScene( random_transition(to_scene) );
}

JigScene* GameSceneMgr::curScene()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    return static_cast<JigScene*>(scene);
}
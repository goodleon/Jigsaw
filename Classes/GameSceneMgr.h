//
//  GameSceneMgr.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-24.
//
//

#ifndef __Jigsaw__GameSceneMgr__
#define __Jigsaw__GameSceneMgr__

#include "cex.h"
#include "JigScene.h"

enum SceneType
{
    kStartScene,
    kThanksScene,
//    kHistoryScene,
    kChooseScene,
    kPlayScene
};

class GameSceneMgr : public cex::Singleton<GameSceneMgr>
{
public:
    void replace(SceneType scene);

    JigScene* curScene();
private:
    SceneType m_curScene;
};

#endif /* defined(__Jigsaw__GameSceneMgr__) */

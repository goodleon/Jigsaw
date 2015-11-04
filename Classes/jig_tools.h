//
//  jig_tools.h
//  Jigsaw
//
//  Created by zhangdw on 15-11-3.
//
//

#ifndef __Jigsaw__jig_tools__
#define __Jigsaw__jig_tools__

#include "JigHeader.h"
#include "JigScene.h"

#define JIG_SCENE_FROM_LAYER(_LAYER_) \
static JigScene* createScene() \
{ \
    JigScene* scene = JigScene::create(); \
    _LAYER_* layer = _LAYER_::create(); \
    scene->addChild(layer); \
    return scene; \
}

#endif /* defined(__Jigsaw__jig_tools__) */

//
//  PlayShared.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-17.
//
//

#ifndef Jigsaw_PlayShared_h
#define Jigsaw_PlayShared_h

#include "cex.h"
#include "lib4cc3x.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "JigScene.h"

using namespace std;
using namespace cex;
using namespace lib4cc3x;
using namespace cocos2d;
using namespace ui;

struct PlayShared
{
    JigScene* play_scene;
    
    PlayShared()
    :play_scene(nullptr)
    {
        CCLOG("zz:PlayShared");
    }
};

extern PlayShared playshared;


#endif

//
//  PlayShared.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-17.
//
//

#ifndef Jigsaw_PlayShared_h
#define Jigsaw_PlayShared_h

#include "JigHeader.h"

#include "JigScene.h"
#include "PlayInitMsg.h"

class TouchPanel;

struct PlayShared
{
    friend class PlayManager;

    PlayShared();
    
    JigScene* play_scene;
    TouchPanel* jig_panel;

    int esptime;

    int rows;
    int cols;

    int cur_level;

    string getJigsaw();
    
    void resetNextlevel();
    void resetAll();

    const PlayInitMsg& config() const;

private:
    PlayInitMsg m_config;
};

extern PlayShared playshared;

#endif

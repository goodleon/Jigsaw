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
#include "PlayInitMsg.pb.h"

class TouchPanel;

struct PlayShared
{
    friend class PlayManager;
    
    JigScene* play_scene;
    TouchPanel* jig_panel;

    int esptime;

    int rows;
    int cols;

    int cur_level;

    void resetNextlevel()
    {
        esptime = -1;
        rows = cols = -1;
    }

    void resetAll()
    {
        play_scene = nullptr;
        jig_panel = nullptr;
        cur_level = -1;
        resetNextlevel();
    }

    PlayShared()
    {
        resetAll();
    }

    const PlayInitMsg& playconfig()
    {
        return config;
    }
private:
    PlayInitMsg config;
};

extern PlayShared playshared;
extern const PlayInitMsg& playconfig();

string getJigBack();
string getJigsaw();

#endif

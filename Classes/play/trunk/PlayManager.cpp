//
//  PlayManager.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-25.
//
//

#include "PlayManager.h"
#include "PlayShared.h"
#include "GameSceneMgr.h"
#include "PauseLayer.h"
#include "DBLevelNotes.h"
#include "DBJigLevel.h"

PlayManager::PlayManager()
{

}

PlayManager::~PlayManager()
{
    
}

void PlayManager::onStateChanged(GameState gs)
{
    if (gs==gs_dead && GameStateMgr::inst().lastState()!=gs_pause)
    {
        playshared.play_scene->alert( PauseLayer::create() );
    }
}

void PlayManager::enterGame(const PlayInitMsg& msg)
{
    GameStateMgr::inst().setKeyListener(this);

    playshared.resetAll();
    
    playshared.config = msg;
    playshared.cur_level = msg.start_jiglevel();
    
    restart();
}

void PlayManager::backToChoose()
{
    playshared.resetAll();
    GameSceneMgr::inst().replace(kStartScene);
}

void PlayManager::restart()
{
    playshared.resetNextlevel();
    reloadResource();
    GameSceneMgr::inst().replace(kPlayScene);
    GameStateMgr::inst().change(gs_prepare);
}

void PlayManager::startNextLevel()
{
    assert( playconfig().choose_level()+1 != playconfig().max_level() );
    ++playshared.cur_level;

    restart();
//    playshared.resetNextlevel();
//    reloadResource();
//    GameSceneMgr::inst().replace(kPlayScene);
}

void PlayManager::saveState()
{
    DBLevelNotes note = DBLevelNotes::readby_level(playconfig().choose_level(), playshared.cur_level);
    if (getstar() > note.star)
    {
        note.star = getstar();
        note.writeby_level();
    }
}

void PlayManager::clearState()
{
    GameStateMgr::inst().clearListener();
    GameStateMgr::inst().change(gs_none);
}

bool PlayManager::finishAllState()
{
    return playshared.cur_level==playconfig().max_level()-1;
}

void PlayManager::reloadResource()
{
    addSpriteFrameByFile( getJigsaw() );

    DBJigLevel data;
    DBJigLevel::readby_level(data, playshared.cur_level);
    playshared.rows = data.rows;
    playshared.cols = data.cols;
}

int PlayManager::getstar()
{
    float percent = lefttime() / (float) playconfig().max_time();
    if (percent>=0 && percent<0.4)
    {
        return 1;
    }
    else if (percent<=0.7)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

int PlayManager::lefttime()
{
    return playconfig().max_time()-playshared.esptime;
}


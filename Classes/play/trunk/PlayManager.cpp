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
#include "DBJigLevel.h"
#include "DBRecord.h"
#include "GifMovieCache.h"

PlayManager::PlayManager()
{

}

PlayManager::~PlayManager()
{
    
}

void PlayManager::onStateChanged(GameState gs)
{
//    if (gs==gs_dead && GameStateMgr::inst().lastState()!=gs_pause)
//    {
//        playshared.play_scene->alert( PauseLayer::create() );
//    }
}

void PlayManager::enterGame(const PlayInitMsg& msg)
{
    GameStateMgr::inst().setKeyListener(this);

    playshared.resetAll();
    
    playshared.m_config = msg;
    playshared.cur_level = msg.start_level();
    CCASSERT(playshared.cur_level<playshared.config().level_count(), "");
    
    restart();
}

void PlayManager::exitGame()
{
    playshared.resetAll();
    GameStateMgr::inst().clearListener();
    GameStateMgr::inst().change(gs_none);

    GifMovieCache::getInstance()->cleanup();

    GameSceneMgr::inst().replace(kStartScene);
}

void PlayManager::restart()
{
    playshared.resetNewlevel();

    GifMovieCache::getInstance()->cleanup();

    reloadResource();

    GameSceneMgr::inst().replace(kPlayScene);
    GameStateMgr::inst().change(gs_prepare);
}

void PlayManager::startNextLevel()
{
    assert( playshared.cur_level+1 != playshared.config().level_count() );
    ++playshared.cur_level;

    restart();
}

void PlayManager::saveRecord()
{
    DBRecord record = DBRecord::readby_level(playshared.config().main_level());
    if (playshared.cur_level > record.sub_level) {
        record.sub_level = playshared.cur_level;
        record.write();
    }
}

bool PlayManager::finishAllState()
{
    return playshared.cur_level==playshared.config().level_count()-1;
}

void PlayManager::reloadResource()
{
//    addSpriteFrameByFile( playshared.getJigsaw() );

    DBJigLevel data;
    DBJigLevel::readby_level(data, playshared.cur_level);
    playshared.rows = data.rows;
    playshared.cols = data.cols;
}


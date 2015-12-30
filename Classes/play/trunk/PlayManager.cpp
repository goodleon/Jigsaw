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
#include "GifMovieCache.h"
#include "DBImageConf.h"
#include "PhotoDown.h"
#include "player_tools.h"
#include "JigToast.h"

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

void PlayManager::enterGame(const ImageInfo& info)
{
    GameStateMgr::inst().setKeyListener(this);
    playshared.resetAll();

    DBImageConf conf = DBImageConf::readby_id(info.conf_id);
//    CCASSERT(img.id>0&&conf.id>0, "");
    playshared.file = PhotoDown::inst().get_full_img(info.img_id);
    playshared.rows = conf.rows;
    playshared.cols = conf.cols;
    playshared.rot  = conf.rot;

    m_cur_image = info;

    restart();
}

void PlayManager::exitGame()
{
    playshared.resetAll();
    GameStateMgr::inst().clearListener();
    GameStateMgr::inst().change(gs_none);

    GifMovieCache::getInstance()->cleanup();

    GameSceneMgr::inst().replace(kChooseScene);
}

void PlayManager::restart()
{
    GifMovieCache::getInstance()->cleanup();

    GameSceneMgr::inst().replace(kPlayScene);
    GameStateMgr::inst().change(gs_prepare);
}

void PlayManager::startNextLevel()
{
    ImageInfo info;
    info.img_id = player_tools::get_next_imgid();
    info.conf_id = 3;
    PlayManager::inst().enterGame(info);
}

void PlayManager::check_save_cur_level()
{
    DBRecord rd;
    rd.img_id = m_cur_image.img_id;
    rd.img_conf = m_cur_image.conf_id;
    if ( player_tools::check_save_record(rd) )
    {
        JigToast::show("has_save_record");
    }
}

const ImageInfo& PlayManager::get_image()
{
    return m_cur_image;
}


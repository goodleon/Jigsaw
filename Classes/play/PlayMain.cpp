

#include "PlayMain.h"
#include "JigScene.h"
#include "RotableTouchPanel.h"
#include "GameSceneMgr.h"
#include "GameState.h"
#include "JigToast.h"
#include "PlayManager.h"
#include "LanguageMgr.h"
#include "JigAudio.h"
#include "WinLayer.h"
#include "player_tools.h"

Scene* PlayMain::createScene()
{
    JigScene* scene = JigScene::create();
    PlayMain* layer = PlayMain::create();
    scene->addChild(layer);
    
    playshared.play_scene = scene;
    
    return scene;
}

PlayMain::PlayMain()
:m_display(nullptr)
{

}

PlayMain::~PlayMain()
{
    
}

bool PlayMain::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
    addChild(root);

    initJigPanel();

    SimpleAudioEngine::getInstance()->playBackgroundMusic( audio_background );
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);

	return true;
}

void PlayMain::onStateChanged(GameState gs)
{
    if (gs==gs_playing)
    {

    }
    else if (gs==gs_win)
    {

    }
}

void PlayMain::initJigPanel()
{
    if (playshared.rot) {
        playshared.jig_panel = RotableTouchPanel::create();
    }
    else{
        playshared.jig_panel = DragonlyTouchPanel::create();
    }

    playshared.jig_panel->reset( playshared.file, playshared.rows, playshared.cols );
    playshared.jig_panel->setPosition( m_game_panel->getContentSize()/2 );
    m_game_panel->addChild( playshared.jig_panel );

    playshared.jig_panel->manageEvent( new TouchPanelSound(playshared.jig_panel) );

    Rect rc_start = m_panel_start->getBoundingBox();
    rc_start.origin -= playshared.jig_panel->getBoundingBox().origin;
    playshared.jig_panel->setStartRect( rc_start );
}

Node* PlayMain::load_csd()
{
    Node* root = CSLoader::createNode("PlayMain.csb");

    Button* btn = nullptr;

    btn = static_cast<Button*>( root->getChildByName("Prelook") );
    btn->addClickEventListener( std::bind(&PlayMain::onClickPrelook, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Finish") );
    btn->addClickEventListener( std::bind(&PlayMain::onClickFinish, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("ReturnMenu") );
    btn->addClickEventListener( std::bind(&PlayMain::onClickReturnMenu, this, placeholders::_1) );

    m_game_panel = static_cast<Layout*>(root->getChildByName("game_panel"));
    m_panel_start = static_cast<Layout*>(m_game_panel->getChildByName("panel_start"));
    
    
    return root;
}


void PlayMain::onClickFinish(Ref* sender)
{
    if (GameStateMgr::inst().curState()==gs_prepare)
    {
        playEffect(audio_btn_error);
        return;
    }

    if (playshared.jig_panel->isAllFinished())
    {
        auto win = WinLayer::create();
//        addChild(win);
        lib4cc3x::getCurScene()->alert(win);

        PlayManager::inst().check_save_cur_level();
        
        playEffect(audio_level_win);
    }
    else
    {
        JigToast::show("unfinish");
    }
}

void PlayMain::onClickPrelook(Ref* sender)
{
    if (m_display) {
        return;
    }

    m_display = PlayDisplay::create();
    getCurScene()->alert(m_display);
    playEffect(audio_btn_error);
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    m_display->onExitEvent = [=](Layer*){
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        m_display = nullptr;
    };
}

void PlayMain::onClickReturnMenu(Ref* sender)
{
    PlayManager::inst().exitGame();
    playEffect(audio_btn);
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}




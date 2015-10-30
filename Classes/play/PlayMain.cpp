

#include "PlayMain.h"
#include "JigScene.h"
#include "RotableTouchPanel.h"
#include "GameSceneMgr.h"
#include "PlayDisplay.h"
#include "GameState.h"
#include "JigToast.h"
#include "PlayManager.h"

Scene* PlayMain::createScene()
{
    JigScene* scene = JigScene::create();
    PlayMain* layer = PlayMain::create();
    scene->addChild(layer);
    
    playshared.play_scene = scene;
    
    return scene;
}

PlayMain::PlayMain()
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

    SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName( playshared.getJigsaw() );

//    if (playconfig().shadow())
//    {
//        JigBackground* bg = JigBackground::create();
//        game->addChild( bg );
//        bg->reset(sf, playshared.rows, playshared.cols);
//    }

    initJigPanel(sf);

	return true;
}

void PlayMain::initJigPanel(SpriteFrame* sf)
{
    if (playshared.config().rotable()) {
        playshared.jig_panel = RotableTouchPanel::create();
    }
    else{
        playshared.jig_panel = DragonlyTouchPanel::create();
    }

    playshared.jig_panel->reset( sf, playshared.rows, playshared.cols );
    playshared.jig_panel->setPosition( m_game_panel->getContentSize()/2 );
    m_game_panel->addChild( playshared.jig_panel );

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
    if (PlayManager::inst().finishAllState())
    {
        PlayManager::inst().exitGame();
        JigToast::show("finished_all");
    }
    else if (playshared.jig_panel->isAllFinished())
    {
        PlayManager::inst().startNextLevel();
//        WinLayer* win = WinLayer::create();
//        getCurScene()->alert(win);
    }
    else
    {
        JigToast::show("unfinish");
//        PlayDisplay* display = PlayDisplay::create();
//        getCurScene()->alert(display);
    }
}

void PlayMain::onClickPrelook(Ref* sender)
{
    PlayDisplay* display = PlayDisplay::create();
    getCurScene()->alert(display);
}

//void PlayMain::onClickPause(Ref* sender)
//{
//    playshared.play_scene->alert( PauseLayer::create() );
//}

void PlayMain::onClickReturnMenu(Ref* sender)
{
    PlayManager::inst().exitGame();
}




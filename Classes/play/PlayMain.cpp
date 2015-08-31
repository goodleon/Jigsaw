

#include "PlayMain.h"
#include "JigScene.h"
#include "RotableTouchPanel.h"
#include "GameSceneMgr.h"
#include "PauseLayer.h"
#include "JigBackground.h"
#include "GameState.h"
#include "TimeHpBar.h"
#include "JigToast.h"
#include "PlayManager.h"
#include "WinLayer.h"

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
    
    Layout* game = static_cast<Layout*>( root->getChildByName("panel_game") );
    
    SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName( getJigsaw() );
    
    if (playconfig().shadow())
    {
        JigBackground* bg = JigBackground::create();
        game->addChild( bg );
        bg->reset(sf, playshared.rows, playshared.cols);
    }
    
    if (playconfig().rotable()) {
        playshared.jig_panel = RotableTouchPanel::create();
    }
    else{
        playshared.jig_panel = DragonlyTouchPanel::create();
    }
    playshared.jig_panel->reset( sf, playshared.rows, playshared.cols);
    playshared.jig_panel->setStartRect( game->getChildByName("panel_start")->getBoundingBox() );
    game->addChild(playshared.jig_panel);
    playshared.jig_panel->setPosition(game->getContentSize()/2);
    
    TimeHpBar* bar = TimeHpBar::create();
    root->addChild(bar);
    bar->setPosition(760, 590);
    
	return true;
}

Node* PlayMain::load_csd()
{
	Node* root = CSLoader::createNode("playmain.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Finish") );
	btn->addClickEventListener( std::bind(&PlayMain::onClickFinish, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Pause") );
	btn->addClickEventListener( std::bind(&PlayMain::onClickPause, this, placeholders::_1) );
    
    return root;
}


void PlayMain::onClickFinish(Ref* sender)
{
    if (playshared.jig_panel->isAllFinished())
    {
        PlayManager::inst().saveState();
        WinLayer* win = WinLayer::create();
        getCurScene()->alert(win);
    }
    else
    {
        JigToast::show("unfinish");
    }
}
			
void PlayMain::onClickPause(Ref* sender)
{
    playshared.play_scene->alert( PauseLayer::create() );
}
			



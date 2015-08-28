

#include "PauseLayer.h"
#include "GameSceneMgr.h"
#include "ConfirmLayer.h"
#include "GameState.h"
#include "PlayManager.h"

PauseLayer::PauseLayer()
{
    GameStateMgr::inst().change(gs_pause);
}

PauseLayer::~PauseLayer()
{

}

bool PauseLayer::init()
{
	Return_False_If(!Layer::init());

	load_csd();

	return true;
}

void PauseLayer::load_csd()
{
	Node* root = CSLoader::createNode("pause.csb");
	addChild(root);

	Button* btn = nullptr;

    btn = static_cast<Button*>( root->getChildByName("Restart") );
    btn->addClickEventListener( std::bind(&PauseLayer::onClickRestart, this, placeholders::_1) );
    
	btn = static_cast<Button*>( root->getChildByName("Continue") );
	btn->addClickEventListener( std::bind(&PauseLayer::onClickContinue, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Mainmenu") );
	btn->addClickEventListener( std::bind(&PauseLayer::onClickMainmenu, this, placeholders::_1) );
}

void PauseLayer::onClickRestart(Ref* sender)
{
    ConfirmLayer* confirm = ConfirmLayer::create("restart", [=](){
        PlayManager::inst().restart();
    }, nullptr);
    
    playshared.play_scene->alert(confirm);
}

void PauseLayer::onClickContinue(Ref* sender)
{
    playshared.play_scene->dismiss(this);
    GameStateMgr::inst().change( GameStateMgr::inst().lastState() );
}

void PauseLayer::onClickMainmenu(Ref* sender)
{
    ConfirmLayer* confirm = ConfirmLayer::create("mainmenu", [=](){
        PlayManager::inst().backToChoose();
    }, nullptr);
    
    playshared.play_scene->alert(confirm);
}




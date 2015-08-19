

#include "PlayMainboard.h"
#include "PauseLayer.h"

PlayMainboard::PlayMainboard()
{

}

PlayMainboard::~PlayMainboard()
{

}

bool PlayMainboard::init()
{
	Return_False_If(!Layer::init());

	load_csd();

	return true;
}

void PlayMainboard::load_csd()
{
	Node* root = CSLoader::createNode("playmain.csb");
    addChild(root);

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Pause") );
	btn->addClickEventListener( std::bind(&PlayMainboard::onClickPause, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Finish") );
	btn->addClickEventListener( std::bind(&PlayMainboard::onClickFinish, this, placeholders::_1) );


	m_time = static_cast<Text*>(root->getChildByName("m_time"));

}


void PlayMainboard::onClickPause(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);

    PauseLayer* layer = PauseLayer::create();
    playshared.play_scene->alert(layer);
}
			
void PlayMainboard::onClickFinish(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);

//    playshared.play_scene->popLayer();
}
			



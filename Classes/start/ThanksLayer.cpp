

#include "ThanksLayer.h"
#include "JigHeader.h"
#include "GameSceneMgr.h"
#include "JigAudio.h"

ThanksLayer::ThanksLayer()
{

}

ThanksLayer::~ThanksLayer()
{

}

JigScene* ThanksLayer::createScene()
{
    JigScene* scene = JigScene::create();
    ThanksLayer* layer = ThanksLayer::create();
    scene->addChild(layer);
    return scene;
}

bool ThanksLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

Node* ThanksLayer::load_csd()
{
	Node* root = CSLoader::createNode("Thanks.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Return") );
	btn->addClickEventListener( std::bind(&ThanksLayer::onClickReturn, this, placeholders::_1) );

	return root;
}


void ThanksLayer::onClickReturn(Ref* sender)
{
    GameSceneMgr::inst().replace(kStartScene);
    playEffect(audio_btn);
}


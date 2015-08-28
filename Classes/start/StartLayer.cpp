

#include "StartLayer.h"
#include "GameSceneMgr.h"
#include "PlayManager.h"
#include "PlayInitMsg.pb.h"

Scene* StartLayer::createScene()
{
    Scene* scene = Scene::create();
    StartLayer* layer = StartLayer::create();
    scene->addChild(layer);
    return scene;
}

StartLayer::StartLayer()
{

}

StartLayer::~StartLayer()
{

}

bool StartLayer::init()
{
	Return_False_If(!Layer::init());

	load_csd();

	return true;
}

void StartLayer::load_csd()
{
	Node* root = CSLoader::createNode("startlayer.csb");
	addChild(root);

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Start") );
	btn->addClickEventListener( std::bind(&StartLayer::onClickStart, this, placeholders::_1) );

}

void StartLayer::onClickStart(Ref* sender)
{
    GameSceneMgr::inst().replace(kChooseLevel);
}




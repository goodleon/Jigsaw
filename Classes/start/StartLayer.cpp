

#include "StartLayer.h"
#include "PlayManager.h"

StartLayer::StartLayer()
{

}

StartLayer::~StartLayer()
{

}

JigScene* StartLayer::createScene()
{
    JigScene* scene = JigScene::create();
    StartLayer* layer = StartLayer::create();
    scene->addChild(layer);
    return scene;
}

bool StartLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

Node* StartLayer::load_csd()
{
	Node* root = CSLoader::createNode("StartLayer.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Start") );
	btn->addClickEventListener( std::bind(&StartLayer::onClickStart, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Thanks") );
	btn->addClickEventListener( std::bind(&StartLayer::onClickThanks, this, placeholders::_1) );



	return root;
}


void StartLayer::onClickStart(Ref* sender)
{
//    GameSceneMgr::inst().replace(kPlayScene);
    PlayInitMsg msg;
    msg.set_choose_level(0);
//    msg.set_max_time(100);
    msg.set_start_jiglevel(0);
    PlayManager::inst().enterGame(msg);
}

void StartLayer::onClickThanks(Ref* sender)
{
	Button* btn = static_cast<Button*>(sender);
	CCLOG("%s", btn->getName().c_str());
}
			





#include "StartLayer.h"
#include "PlayManager.h"
#include "GameSceneMgr.h"
#include "version.h"

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

    m_version->setString( sstr("v.%d.%d", major_version, minor_version) );

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

    m_version = static_cast<Text*>( root->getChildByName("version") );

	return root;
}


void StartLayer::onClickStart(Ref* sender)
{
    PlayInitMsg msg;
    msg.set_max_level(2);
    msg.set_rotable(true);
    PlayManager::inst().enterGame(msg);
}

void StartLayer::onClickThanks(Ref* sender)
{
    GameSceneMgr::inst().replace(kThanksScene);
}






#include "StartLayer.h"
#include "PlayManager.h"
#include "GameSceneMgr.h"
#include "DBRecord.h"
#include "DBMainLevel.h"
#include "version.h"
#include "PaymentMgr.h"
#include "JigAudio.h"

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

    m_version->setString( sstr("v.%s", get_version().c_str()) );

    PaymentMgr::inst().init();
    
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
    DBRecord record = DBRecord::readby_level(0);
    if (record.main_level==0 && record.sub_level<0)
    {
        DBMainLevel level = DBMainLevel::readby_level(0);
        PlayInitMsg msg;
        msg.set_main_level( 0 );
        msg.set_start_level( 0 );
        msg.set_level_count( level.Count );
        msg.set_rotable( level.Rotable );
        PlayManager::inst().enterGame(msg);
    }
    else
    {
        GameSceneMgr::inst().replace( kHistoryScene );
    }

    playEffect(audio_btn);
}

void StartLayer::onClickThanks(Ref* sender)
{
    GameSceneMgr::inst().replace(kThanksScene);
    playEffect(audio_btn);
}




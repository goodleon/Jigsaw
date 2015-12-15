

#include "StartLayer.h"
#include "PlayManager.h"
#include "GameSceneMgr.h"
#include "version.h"
#include "PaymentMgr.h"
#include "JigAudio.h"
#include "Network.h"
#include "ClientCenter.h"
#include "JigToast.h"

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

void StartLayer::onMessage(int notify_id, const net_data_t& root)
{
    if (notify_id == proto_login_down)
    {
        m_userid->setString( sstr("%d", ClientCenter::inst().user_id) );
    }
    else if (notify_id == proto_check_network_down)
    {
        Request req(proto_login_up);
        Network::inst().addRequest(req);
    }
}

bool StartLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    m_version->setString( sstr("v.%s", get_version().c_str()) );
    m_userid->setString( sstr("%d", ClientCenter::inst().user_id) );
    
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
    m_userid = static_cast<Text*>( root->getChildByName("userid") );

	return root;
}


void StartLayer::onClickStart(Ref* sender)
{
    if (ClientCenter::inst().user_id==0) {
        Request req(proto_login_up);
        Network::inst().addRequest(req);
        JigToast::show("login_fail_retry");
    }
    else {
        this->scheduleOnce([](float){
            GameSceneMgr::inst().replace( kChooseScene );
        }, 0, "enter_history_lazy");
    }
    playEffect(audio_btn);
}

void StartLayer::onClickThanks(Ref* sender)
{
    GameSceneMgr::inst().replace(kThanksScene);
    playEffect(audio_btn);
}




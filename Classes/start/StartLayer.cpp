

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

bool StartLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    m_version->setString( sstr("v.%s", get_version().c_str()) );
    
	return true;
}

Node* StartLayer::load_csd()
{
    Node* root = CSLoader::createNode("StartLayer.csb");

    Button* btn = nullptr;

    btn = static_cast<Button*>( root->getChildByName("Double") );
    btn->addClickEventListener( std::bind(&StartLayer::onClickDouble, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Single") );
    btn->addClickEventListener( std::bind(&StartLayer::onClickSingle, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Thanks") );
    btn->addClickEventListener( std::bind(&StartLayer::onClickThanks, this, placeholders::_1) );


    m_Image_1 = static_cast<ImageView*>(root->getChildByName("Image_1"));

    m_version = static_cast<Text*>(root->getChildByName("version"));
    
    
    return root;
}


void StartLayer::onClickSingle(Ref* sender)
{
//    if (ClientCenter::inst().user_id==0) {
//        Request req(proto_login_up);
//        Network::inst().addRequest(req);
//        JigToast::show("login_fail_retry");
//    }
//    else {
//        this->scheduleOnce([](float){
//            GameSceneMgr::inst().replace( kChooseScene );
//        }, 0, "enter_history_lazy");
//    }
    GameSceneMgr::inst().replace( kChooseScene );
    playEffect(audio_btn);
}

void StartLayer::onClickDouble(Ref* sender)
{
    Button* btn = static_cast<Button*>(sender);
    CCLOG("%s", btn->getName().c_str());
}

void StartLayer::onClickThanks(Ref* sender)
{
    GameSceneMgr::inst().replace(kThanksScene);
    playEffect(audio_btn);
}




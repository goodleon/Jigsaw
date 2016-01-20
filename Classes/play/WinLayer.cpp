

#include "WinLayer.h"
#include "JigToast.h"
#include "GameSceneMgr.h"
#include "PlayShared.h"
#include "player_tools.h"
#include "ChooseLayer.h"
#include "PlayManager.h"

WinLayer::WinLayer()
{

}

WinLayer::~WinLayer()
{

}

bool WinLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    const ImageInfo info = PlayManager::inst().get_image();
    const string cond = sstr("img_id=%d", info.img_id);
    const DBRecord rd = DBRecord::readby_condition(cond);
    m_highest->setString( sstr("%d", player_tools::calc_score(rd.img_conf)) );

    m_cur_score->setString( sstr("%d", player_tools::calc_score(info.conf_id)) );

    root->setPosition(Director::getInstance()->getWinSize()/2);
    root->setAnchorPoint(Point(0.5f, 0.5f));
//    root->setScale(0.2f);
//    root->runAction( ScaleTo::create(0.3f, 1.0f) );

	return true;
}

Node* WinLayer::load_csd()
{
    Node* root = CSLoader::createNode("WinLayer.csb");

    Button* btn = nullptr;

    btn = static_cast<Button*>( root->getChildByName("Return") );
    btn->addClickEventListener( std::bind(&WinLayer::onClickReturn, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Next") );
    btn->addClickEventListener( std::bind(&WinLayer::onClickNext, this, placeholders::_1) );


    m_Image_1 = static_cast<ImageView*>(root->getChildByName("Image_1"));

    m_cur_score = static_cast<Text*>(root->getChildByName("cur_score"));

    m_Image_2 = static_cast<ImageView*>(root->getChildByName("Image_2"));

    m_Text_1_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0"));

    m_highest = static_cast<Text*>(root->getChildByName("highest"));

    m_Text_1 = static_cast<Text*>(root->getChildByName("Text_1"));
    
    
    return root;
}

void WinLayer::onClickNext(Ref* sender)
{
    PlayManager::inst().startNextLevel();
}

void WinLayer::onClickReturn(Ref* sender)
{
    GameSceneMgr::inst().replace(kChooseScene);
}




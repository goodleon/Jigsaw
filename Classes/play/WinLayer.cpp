

#include "WinLayer.h"
#include "JigToast.h"
#include "GameSceneMgr.h"

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

	return true;
}

void WinLayer::onMessage(int notify_id, const net_data_t& root)
{
    if (notify_id == proto_start_play_end_down)
    {
        int highest = root["highest"].GetInt();
        float used_time = root["used_time"].GetDouble();
        int cur_score = root["cur_score"].GetInt();
        m_highest->setString( sstr("%d", highest) );
        m_cur_time->setString( sstr("%.2f", used_time) );
        m_cur_score->setString( sstr("%d", cur_score));
    }
}

Node* WinLayer::load_csd()
{
	Node* root = CSLoader::createNode("WinLayer.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Cupboard") );
	btn->addClickEventListener( std::bind(&WinLayer::onClickCupboard, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Return") );
	btn->addClickEventListener( std::bind(&WinLayer::onClickReturn, this, placeholders::_1) );


	m_Image_1 = static_cast<ImageView*>(root->getChildByName("Image_1"));

	m_cur_score = static_cast<Text*>(root->getChildByName("cur_score"));

	m_Text_1_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0"));

	m_Text_1_0 = static_cast<Text*>(root->getChildByName("Text_1_0"));

	m_cur_time = static_cast<Text*>(root->getChildByName("cur_time"));

	m_highest = static_cast<Text*>(root->getChildByName("highest"));

	m_Text_1 = static_cast<Text*>(root->getChildByName("Text_1"));


	return root;
}


void WinLayer::onClickCupboard(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);
//	CCLOG("%s", btn->getName().c_str());
    JigToast::show("canot_use");
}

void WinLayer::onClickReturn(Ref* sender)
{
    GameSceneMgr::inst().replace(kChooseScene);
}




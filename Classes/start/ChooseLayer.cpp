

#include "ChooseLayer.h"
#include "JigToast.h"
#include "GameSceneMgr.h"
#include "Network.h"
#include "PhotoDown.h"
#include "DBImage.h"
#include "DBImageConf.h"
#include "JigSprite.h"
#include "LanguageMgr.h"
#include "PlayManager.h"

ChooseLayer::ChooseLayer()
{
    m_info.img_id = 0;
    m_info.conf_id = 0;
    m_info.start_time = 0;
    m_info.pass = false;
}

ChooseLayer::~ChooseLayer()
{

}

bool ChooseLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    initRadio();

    Request req(proto_get_progress_up);
    Network::inst().addRequest(req);

	return true;
}

void ChooseLayer::initRadio()
{
    m_radio.addItem(m_check0);
    m_radio.addItem(m_check1);
    m_radio.addItem(m_check2);
    m_radio.addItem(m_check3);
    m_radio.onChange = [=](int idx){
        this->updateScore();
    };

    m_check_rot->addEventListener( [=](Ref*, CheckBox::EventType){
        this->updateScore();
    });
}

void ChooseLayer::updateScore()
{
    int score = m_radio.getSelectedIdx()*150 + 300;
    score *= m_check_rot->isSelected() ? 2 : 1;
    m_score->setString( sstr("%d", score) );

    m_info.conf_id = m_radio.getSelectedIdx()*2+1;
    m_info.conf_id += m_check_rot->isSelected() ? 1 : 0;
}

Node* ChooseLayer::load_csd()
{
    Node* root = CSLoader::createNode("ChooseLayer.csb");

    Button* btn = nullptr;

    btn = static_cast<Button*>( root->getChildByName("SplitBar") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickSplitBar, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Start") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickStart, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Jump") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickJump, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Return") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickReturn, this, placeholders::_1) );

    m_check_rot = static_cast<CheckBox*>(root->getChildByName("check_rot"));

    m_Text_1_0_0_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0_0_0"));

    m_Text_1_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0"));

    m_Text_1_0_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0_0"));

    m_score = static_cast<Text*>(root->getChildByName("score"));

    m_img_bg = static_cast<ImageView*>(root->getChildByName("img_bg"));

    m_Text_6 = static_cast<Text*>(root->getChildByName("Text_6"));

    m_Text_1_0 = static_cast<Text*>(root->getChildByName("Text_1_0"));

    m_Text_1 = static_cast<Text*>(root->getChildByName("Text_1"));

    m_check2 = static_cast<CheckBox*>(root->getChildByName("check2"));

    m_check3 = static_cast<CheckBox*>(root->getChildByName("check3"));

    m_check0 = static_cast<CheckBox*>(root->getChildByName("check0"));
    
    m_check1 = static_cast<CheckBox*>(root->getChildByName("check1"));
    
    
    return root;
}



void ChooseLayer::onClickReturn(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);
//	CCLOG("%s", btn->getName().c_str());
    GameSceneMgr::inst().replace(kStartScene);
}

void ChooseLayer::onClickSplitBar(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);
//	CCLOG("%s", btn->getName().c_str());
    JigToast::show("iamsplit");
}

void ChooseLayer::onClickStart(Ref* sender)
{
    Request req(proto_enter_gamescene_up);
    req.append("img_id", m_info.img_id);
    req.append("conf_id", m_info.conf_id);
    Network::inst().addRequest(req);

    PlayManager::inst().enterGame(m_info);
}

void ChooseLayer::onClickJump(Ref* sender)
{
    if (!m_info.pass)
    {
        JigToast::show("at_least_finish_one");
    }
    else
    {
        Request req(proto_refresh_progress_up);
        Network::inst().addRequest(req);
    }
}

void ChooseLayer::onMessage(int notify_id, const net_data_t& root)
{
    if (notify_id == proto_get_progress_down)
    {
        m_info.img_id = root["img_id"].GetInt();
        m_info.conf_id = root["conf_id"].GetInt();
        m_info.start_time = root["start_time"].GetDouble();
        m_info.pass = root["pass"].GetInt();
        PhotoDown::inst().load(m_info.img_id);
    }
    else if (notify_id == notify_img_complete_one)
    {
        refreshImg();
        refreshConfig();
    }
}

void ChooseLayer::refreshImg()
{
    DBImage img = DBImage::readby_id(m_info.img_id);
    string file = PhotoDown::inst().get_full_img(img.name);
    if (!FileUtils::getInstance()->isFileExist(file)) {
        JigToast::show( LanguageMgr::inst().getText("can_not_find_img")+img.name );
        return;
    }

    const Size selfSize = m_img_bg->getContentSize();

    Sprite* sp = Sprite::create("res/back4.png");
    sp->setPosition(selfSize/2);
    m_img_bg->addChild(sp);

    Sprite* stencil = Sprite::create("res/back4.png");
    ClippingNode* clip = ClippingNode::create(stencil);
    clip->setPosition(selfSize/2);
    clip->setAlphaThreshold(0.1f);
    clip->setScale(0.985);
    m_img_bg->addChild(clip);

    GifBase* gif = JigSprite::create( file );
    const Size content = gif->getContentSize();
    gif->setScale( selfSize.width/content.width );
    clip->addChild(gif);
}

void ChooseLayer::refreshConfig()
{
    DBImageConf conf = DBImageConf::readby_id(m_info.conf_id);
    if (conf.id<=0) {
        JigToast::show("conf is error");
        return;
    }

    m_check_rot->setSelected( conf.rot );
    m_radio.setSelected( conf.rows-3 );
}


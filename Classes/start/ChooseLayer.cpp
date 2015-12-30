

#include "ChooseLayer.h"
#include "JigToast.h"
#include "GameSceneMgr.h"
#include "PhotoDown.h"
#include "DBImageConf.h"
#include "JigSprite.h"
#include "LanguageMgr.h"
#include "PlayManager.h"
#include "player_tools.h"

ChooseLayer::ChooseLayer()
{
    m_info.img_id = 0;
    m_info.conf_id = 0;
//    m_info.start_time = 0;
//    m_info.pass = false;
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

    m_info.img_id = player_tools::get_next_imgid();
    refreshImg();

    m_info.conf_id = 3;
    refreshConfig();
    
	return true;
}

void ChooseLayer::initRadio()
{
    m_radio.addItem(m_check0);
    m_radio.addItem(m_check1);
    m_radio.addItem(m_check2);
    m_radio.addItem(m_check3);
    m_radio.onChange = [=](int idx){
        this->updateConfig();
    };

    m_check_rot->addEventListener( [=](Ref*, CheckBox::EventType){
        this->updateConfig();
    });
}

void ChooseLayer::updateConfig()
{
    m_info.conf_id = m_radio.getSelectedIdx()*2+1;
    m_info.conf_id += m_check_rot->isSelected() ? 1 : 0;

    const int score = player_tools::calc_score(m_info.conf_id);
    m_score->setString( sstr("%d", score) );
}

Node* ChooseLayer::load_csd()
{
    Node* root = CSLoader::createNode("ChooseLayer.csb");

    Button* btn = nullptr;

    btn = static_cast<Button*>( root->getChildByName("SplitBar") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickSplitBar, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Start") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickStart, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Next") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickNext, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Last") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickLast, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Newest") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickNewest, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Return") );
    btn->addClickEventListener( std::bind(&ChooseLayer::onClickReturn, this, placeholders::_1) );


    m_level = static_cast<TextAtlas*>(root->getChildByName("level"));

    m_check_rot = static_cast<CheckBox*>(root->getChildByName("check_rot"));

    m_Text_1_0 = static_cast<Text*>(root->getChildByName("Text_1_0"));

    m_Text_1_0_0_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0_0_0"));

    m_Text_1_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0"));

    m_Text_1_0_0_0 = static_cast<Text*>(root->getChildByName("Text_1_0_0_0"));

    m_score = static_cast<Text*>(root->getChildByName("score"));

    m_img_bg = static_cast<ImageView*>(root->getChildByName("img_bg"));

    m_Text_6 = static_cast<Text*>(root->getChildByName("Text_6"));

    m_check1 = static_cast<CheckBox*>(root->getChildByName("check1"));

    m_check2 = static_cast<CheckBox*>(root->getChildByName("check2"));

    m_check3 = static_cast<CheckBox*>(root->getChildByName("check3"));
    
    m_check0 = static_cast<CheckBox*>(root->getChildByName("check0"));
    
    m_Text_1 = static_cast<Text*>(root->getChildByName("Text_1"));
    
    
    return root;
}

void ChooseLayer::onClickReturn(Ref* sender)
{
    GameSceneMgr::inst().replace(kStartScene);
}

void ChooseLayer::onClickSplitBar(Ref* sender)
{
    JigToast::show("iamsplit");
}

void ChooseLayer::onClickStart(Ref* sender)
{
    PlayManager::inst().enterGame(m_info);
}

void ChooseLayer::onClickNext(Ref* sender)
{
    const int nextid = player_tools::get_next_imgid();
    if (nextid==m_info.img_id)
    {
        JigToast::show("last_to_first");
        m_info.img_id = 1;
    }
    else
    {
        m_info.img_id++;
    }

    refreshImg();

    m_info.conf_id = 3;
    refreshConfig();
}

void ChooseLayer::onClickLast(Ref* sender)
{
    const int nextid = player_tools::get_next_imgid();
    if (m_info.img_id==1)
    {
        JigToast::show("first_to_last");
        m_info.img_id = nextid;
    }
    else
    {
        --m_info.img_id;
    }

    refreshImg();

    m_info.conf_id = 3;
    refreshConfig();
}

void ChooseLayer::onClickNewest(Ref* sender)
{
    const int newest = player_tools::get_next_imgid();
    m_info.img_id = newest;
    refreshImg();

    m_info.conf_id = 3;
    refreshConfig();
}

void ChooseLayer::refreshImg()
{
    if (!PhotoDown::inst().isFileExist(m_info.img_id)) {
        JigToast::show( LanguageMgr::inst().getText("can_not_find_img")+sstr("id=%d", m_info.img_id) );
        return;
    }

    m_level->setString( cstr("%d", m_info.img_id) );

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

    string file = PhotoDown::inst().get_full_img(m_info.img_id);
    GifBase* gif = JigSprite::create( file );
    const Size content = gif->getContentSize();
    gif->setScale( selfSize.width/content.width );
    clip->addChild(gif);
}

void ChooseLayer::refreshConfig()
{
    m_check_rot->setSelected( m_info.conf_id%2==0 );
    m_radio.setSelected( (m_info.conf_id-1)/2 );
    updateConfig();
}




#include "ChooseLevelItem.h"
#include "JigToast.h"
#include "PlayInitMsg.pb.h"
#include "PlayManager.h"
#include "DBLevelNotes.h"
#include "DBMainLevel.h"
#include "LevelPassView.h"

ChooseLevelItem::ChooseLevelItem()
:m_bUnlock(false)
{

}

ChooseLevelItem::~ChooseLevelItem()
{

}

bool ChooseLevelItem::init()
{
	Return_False_If(!Node::init());

	Node* root = load_csd();
	addChild(root);
    
    m_img->setTouchEnabled(false);

	return true;
}

Node* ChooseLevelItem::load_csd()
{
	Node* root = CSLoader::createNode("chooselevelitem.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Item") );
	btn->addClickEventListener( std::bind(&ChooseLevelItem::onClickItem, this, placeholders::_1) );
    m_btn = btn;
    
    m_img = static_cast<ImageView*>(root->getChildByName("img"));

	return root;
}


void ChooseLevelItem::onClickItem(Ref* sender)
{
//    if (m_bUnlock)
//    {
//        JigToast::show("pre_unfinish");
//    }
//    else
    {
        LevelPassView* info = LevelPassView::create();
        info->reset(m_iMainLevel);
        Point pt = getPosition();//cocos2array(getPosition(), getParent());
        pt += Point(100, 100);
//        pt = Point::ZERO;
        getCurScene()->showTip(info, pt);
//        DBMainLevel data;
//        DBMainLevel::readby_level(data, m_iMainLevel);
//
//        DBLevelNotes jig;
//        for (int i=data.min_jiglevel; i<data.max_jiglevel; ++i)
//        {
//            DBLevelNotes::readby_level(jig, m_iMainLevel, i);
//            Break_If(jig.star!=3);
//        }
//
//        PlayInitMsg msg;
//        msg.set_choose_level( m_iMainLevel );
//        msg.set_start_jiglevel(jig.jiglevel);
//        msg.set_max_level( data.max_jiglevel );
//        msg.set_max_time(20);
//        PlayManager::inst().enterGame(msg);
    }
}

void ChooseLevelItem::reset(int iMainLevel)
{
    m_iMainLevel = iMainLevel;
    
    m_btn->loadTextureNormal( sstr("jigsaw/level%d/btntitle.png", iMainLevel) );

    if (iMainLevel==0)
    {
        m_bUnlock = false;
    }
    else
    {
        DBMainLevel main;
        DBMainLevel::readby_level(main, iMainLevel-1);

//        int total_star = 0;
//        for (int i=main.min_jiglevel; i<main.max_jiglevel; ++i)
//        {
//            DBLevelNotes pre;
//            DBLevelNotes::readby_level(pre, iMainLevel-1, i);
//            total_star += pre.star;
//        }

        DBLevelNotes pre;
        DBLevelNotes::readby_level(pre, iMainLevel-1, main.max_jiglevel-1);

        m_bUnlock = pre.star<3;
    }

    if (m_bUnlock) {
        m_btn->setColor( Color3B{20, 20, 20} );
    }
}


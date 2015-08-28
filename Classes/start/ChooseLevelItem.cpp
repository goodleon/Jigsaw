

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
    if (m_bUnlock)
    {
        JigToast::show("pre_unfinish");
    }
    else
    {
        LevelPassView* info = LevelPassView::create();
        info->reset(m_iMainLevel);
        Point pt = getPosition();
        pt += Point(100, 100);
        getCurScene()->showTip(info, pt);
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

        DBLevelNotes pre;
        DBLevelNotes::readby_level(pre, iMainLevel-1, main.max_jiglevel-1);

        m_bUnlock = (pre.star==0);
    }

    if (m_bUnlock) {
        m_btn->setColor( Color3B{20, 20, 20} );
    }
}


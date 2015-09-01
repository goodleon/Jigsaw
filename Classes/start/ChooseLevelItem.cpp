

#include "ChooseLevelItem.h"
#include "JigToast.h"
#include "DBMainLevel.h"
#include "DBLevelNotes.h"
#include "LevelPassView.h"

ChooseLevelItem::ChooseLevelItem()
:m_mainLevel(-1)
{

}

ChooseLevelItem::~ChooseLevelItem()
{

}

bool ChooseLevelItem::init()
{
	Return_False_If(!Widget::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

Node* ChooseLevelItem::load_csd()
{
	Node* root = CSLoader::createNode("chooselevelitem.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Button") );
	btn->addClickEventListener( std::bind(&ChooseLevelItem::onClickButton, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Lock") );
    btn->addClickEventListener( std::bind(&ChooseLevelItem::onClickLock, this, placeholders::_1) );
    m_lock = btn;



	return root;
}


void ChooseLevelItem::onClickButton(Ref* sender)
{
    LevelPassView* view = LevelPassView::create();
    view->reset(m_mainLevel);
    getCurScene()->showTip(view, getPosition()+Point(200, 0));
}
			
void ChooseLevelItem::onClickLock(Ref* sender)
{
    JigToast::show("pre_unfinish");
}

void ChooseLevelItem::reset(int level)
{
    if (level==0)
    {
        m_lock->setVisible(false);
    }
    else
    {
        DBMainLevel premain = DBMainLevel::readby_level(level-1);
        DBLevelNotes pre = DBLevelNotes::readby_level(level-1, premain.max_jiglevel-1);
        m_lock->setVisible(pre.star==0);
    }

    m_mainLevel = level;
}


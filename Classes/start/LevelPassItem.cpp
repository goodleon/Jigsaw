

#include "LevelPassItem.h"
#include "LanguageMgr.h"
#include "PlayManager.h"
#include "DBMainLevel.h"
#include "DBJigLevel.h"
#include "JigToast.h"

LevelPassItem::LevelPassItem()
:m_stars(3)
{

}

LevelPassItem::~LevelPassItem()
{

}

bool LevelPassItem::init()
{
	Return_False_If(!Widget::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

void LevelPassItem::reset(const DBLevelNotes& item)
{
    for (int i=0; i<m_stars.size(); ++i)
    {
        m_stars.at(i)->setVisible( i<item.star );
    }

    string lan_id = sstr("level%d", item.jiglevel);
    m_level->setString( LanguageMgr::inst().getText(lan_id) );

    m_data = item;
}

Node* LevelPassItem::load_csd()
{
	Node* root = CSLoader::createNode("levelpassitem.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Button") );
	btn->addClickEventListener( std::bind(&LevelPassItem::onClickButton, this, placeholders::_1) );


	m_stars[2] = static_cast<ImageView*>(root->getChildByName("star2"));
	m_stars[1] = static_cast<ImageView*>(root->getChildByName("star1"));
	m_stars[0] = static_cast<ImageView*>(root->getChildByName("star0"));

	m_level = static_cast<Text*>(root->getChildByName("level"));


	return root;
}


void LevelPassItem::onClickButton(Ref* sender)
{
    if (!canEnter())
    {
        JigToast::show("pre_unfinish");
    }
    else
    {
        DBMainLevel main;
        DBMainLevel::readby_level(main, m_data.level);

        PlayInitMsg msg;
        msg.set_choose_level( m_data.level );
        msg.set_start_jiglevel( m_data.jiglevel );
        msg.set_max_level( main.max_jiglevel );
        msg.set_max_time(100);
        PlayManager::inst().enterGame(msg);
    }
}
			
bool LevelPassItem::canEnter()
{
    Return_True_If(m_data.jiglevel==0);

    DBLevelNotes note;
    DBLevelNotes::readby_level(note, m_data.level, m_data.jiglevel-1);
    return note.star>0;
}


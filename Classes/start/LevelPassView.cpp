

#include "LevelPassView.h"
#include "DBLevelNotes.h"
#include "DBMainLevel.h"
#include "LevelPassItem.h"

LevelPassView::LevelPassView()
{

}

LevelPassView::~LevelPassView()
{

}

bool LevelPassView::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);
    setContentSize( Size(240, 450) );

	return true;
}

void LevelPassView::reset(int iMainLevel)
{
    DBMainLevel main;
    DBMainLevel::readby_level(main, iMainLevel);

    for (int i=main.min_jiglevel; i<main.max_jiglevel; ++i)
    {
        DBLevelNotes note;
        DBLevelNotes::readby_level(note, iMainLevel, i);

        LevelPassItem* item = LevelPassItem::create();
        item->reset( note );
        m_scroll->pushBackCustomItem(item);
    }

}

Node* LevelPassView::load_csd()
{
	Node* root = CSLoader::createNode("levelpass.csb");

	Button* btn = nullptr;


	m_scroll = static_cast<ListView*>(root->getChildByName("scroll"));


	return root;
}





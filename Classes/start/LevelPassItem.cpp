

#include "LevelPassItem.h"

LevelPassItem::LevelPassItem()
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
    
}

Node* LevelPassItem::load_csd()
{
	Node* root = CSLoader::createNode("levelpassitem.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Button") );
	btn->addClickEventListener( std::bind(&LevelPassItem::onClickButton, this, placeholders::_1) );


	m_star2 = static_cast<ImageView*>(root->getChildByName("star2"));

	m_star1 = static_cast<ImageView*>(root->getChildByName("star1"));

	m_star0 = static_cast<ImageView*>(root->getChildByName("star0"));

	m_level = static_cast<Text*>(root->getChildByName("level"));


	return root;
}


void LevelPassItem::onClickButton(Ref* sender)
{
	Button* btn = static_cast<Button*>(sender);
	CCLOG("%s", btn->getName().c_str());
}
			



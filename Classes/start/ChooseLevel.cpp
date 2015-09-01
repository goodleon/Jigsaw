

#include "ChooseLevel.h"
#include "DBMainLevel.h"
#include "ChooseLevelItem.h"
#include "GameSceneMgr.h"
#include "JigToast.h"

JigScene* ChooseLevel::createScene()
{
    JigScene* scene = JigScene::create();
    ChooseLevel* layer = ChooseLevel::create();
    scene->addChild(layer);
    return scene;
}

ChooseLevel::ChooseLevel()
{

}

ChooseLevel::~ChooseLevel()
{

}

bool ChooseLevel::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    for (int i=0; i<m_max_level; ++i)
    {
//        DBMainLevel main;
//        DBMainLevel::readby_level(main, i);
        const int r = 1-i/5;
        const int c = i%5;

        ChooseLevelItem* item = ChooseLevelItem::create();
        item->setPosition(Point(c*150+20, r*150+200));
        item->reset(i);
        m_scroll->addWidgetToPage(item, 0, true);
    }



	return true;
}

Node* ChooseLevel::load_csd()
{
	Node* root = CSLoader::createNode("chooselevel.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Close") );
	btn->addClickEventListener( std::bind(&ChooseLevel::onClickClose, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Right") );
	btn->addClickEventListener( std::bind(&ChooseLevel::onClickRight, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Left") );
	btn->addClickEventListener( std::bind(&ChooseLevel::onClickLeft, this, placeholders::_1) );


	m_scroll = static_cast<PageView*>(root->getChildByName("scroll"));


	return root;
}


void ChooseLevel::onClickClose(Ref* sender)
{
    GameSceneMgr::inst().replace(kStartScene);
}

void ChooseLevel::onClickRight(Ref* sender)
{
    JigToast::show("unopen");
}

void ChooseLevel::onClickLeft(Ref* sender)
{
	JigToast::show("unopen");
}
			



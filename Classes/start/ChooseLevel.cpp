

#include "ChooseLevel.h"
#include "GameSceneMgr.h"
#include "DBLevelNotes.h"
#include "DBMainLevel.h"

JigScene* ChooseLevel::createScene()
{
    JigScene* scene = JigScene::create();
    ChooseLevel* layer = ChooseLevel::create();
    scene->pushLayer(layer);
    
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
    
    m_page->addEventListener( std::bind( &ChooseLevel::onPageEvent, this, placeholders::_1, placeholders::_2  ) );
    
//    vector<ChooseItemMsg> cfg = load_config();

    for (int i=0; i<max_level; ++i)
    {
        const int page = i/6;//每页显示6关
        
        const int r = (i%6) / 3;
        const int c = (i%6) % 3;
        const Point pt(300*c+180, 230*r+120);
        
        ChooseLevelItem* item = ChooseLevelItem::create();
        item->reset( i );
        m_page->addWidgetToPage( item, page, true );
        
        item->setPosition( cocos2array( pt, m_page ) );
    }
    
	return true;
}

Node* ChooseLevel::load_csd()
{
	Node* root = CSLoader::createNode("chooselevel.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Return") );
	btn->addClickEventListener( std::bind(&ChooseLevel::onClickReturn, this, placeholders::_1) );

    m_page_idx = static_cast<Text*>(root->getChildByName("page_idx"));

	m_page = static_cast<PageView*>(root->getChildByName("page"));


	return root;
}


void ChooseLevel::onClickReturn(Ref* sender)
{
    GameSceneMgr::inst().replace(kStartScene);
}

void ChooseLevel::onPageEvent(Ref*, PageView::EventType evt)
{
    if (evt == PageView::EventType::TURNING)
    {
        string str = sstr("%d/%d", m_page->getCurPageIndex()+1, m_page->getPages().size());
        m_page_idx->setString( str );
    }
}

//vector<ChooseItemMsg> ChooseLevel::load_config()
//{
//    vector<ChooseItemMsg> ret;
//    for (int i=0; i<max_level; ++i)
//    {
//        DBLevelNotes note;
//        DBLevelNotes::readby_level(note, i, 0);
//        
//        ChooseItemMsg msg;
//        msg.set_level( note.level );
//        msg.set_star( note.star );
//        
//        ret.push_back( msg );
//    }
//    
//    ret.at(0).set_canchoose(true);
//    for (int i=1; i<max_level; ++i)
//    {
//        ret.at(i).set_canchoose( ret.at(i-1).star()==3 );
//    }
//    
//    return ret;
//}

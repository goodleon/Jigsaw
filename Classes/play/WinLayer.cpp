

#include "WinLayer.h"
#include "PlayManager.h"
#include "GameSceneMgr.h"

WinLayer::WinLayer()
:m_stars(3)
{

}

WinLayer::~WinLayer()
{

}

bool WinLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    for (int i=0; i<m_stars.size(); ++i)
    {
        m_stars.at(i)->setVisible( i<PlayManager::inst().getstar() );

        DelayTime* delay = DelayTime::create(0.1+i*0.5);
        ScaleTo* scale = ScaleTo::create(0.2, 1.2f);
        ScaleTo* scale2 = ScaleTo::create(0.05, 1.0f);
        Sequence* seq = Sequence::create(delay, scale, scale2, nullptr);
        m_stars.at(i)->setScale(0);
        m_stars.at(i)->runAction( seq );
    }

	return true;
}

Node* WinLayer::load_csd()
{
	Node* root = CSLoader::createNode("winlayer.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Restart") );
	btn->addClickEventListener( std::bind(&WinLayer::onClickRestart, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("MainMenu") );
	btn->addClickEventListener( std::bind(&WinLayer::onClickMainMenu, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Next") );
	btn->addClickEventListener( std::bind(&WinLayer::onClickNext, this, placeholders::_1) );

    m_stars.at(0) = static_cast<ImageView*>( root->getChildByName("star0") );
    m_stars.at(1) = static_cast<ImageView*>( root->getChildByName("star1") );
    m_stars.at(2) = static_cast<ImageView*>( root->getChildByName("star2") );

	return root;
}


void WinLayer::onClickRestart(Ref* sender)
{
    PlayManager::inst().restart();
}
			
void WinLayer::onClickMainMenu(Ref* sender)
{
    PlayManager::inst().backToChoose();
}
			
void WinLayer::onClickNext(Ref* sender)
{
    if ( PlayManager::inst().finishAllState() )
    {
        GameSceneMgr::inst().replace(kStartScene);
    }
    else
    {
        PlayManager::inst().startNextLevel();
    }
}






#include "PlayDisplay.h"
#include "PlayShared.h"
#include "CacheGif.h"

PlayDisplay::PlayDisplay()
{

}

PlayDisplay::~PlayDisplay()
{

}

bool PlayDisplay::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    m_back->addTouchEventListener( std::bind(&PlayDisplay::onTouchPanel,this,placeholders::_1, placeholders::_2) );

    CacheGif* gif = CacheGif::create( playshared.getJigsaw().c_str() );
    gif->setPosition(m_img->getContentSize()/2);
    gif->setScale( m_img->getContentSize().width/gif->getContentSize().width );
    m_img->addChild(gif);

	return true;
}

Node* PlayDisplay::load_csd()
{
	Node* root = CSLoader::createNode("Preview.csb");

//	Button* btn = nullptr;


	m_back = static_cast<ImageView*>( root->getChildByName("back") );
    m_img = static_cast<ImageView*>( root->getChildByName("img") );

	return root;
}

void PlayDisplay::onTouchPanel(Ref*, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        getCurScene()->dismiss(this);
    }
}





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

    ClippingNode* clip = ClippingNode::create();
    m_clip_stencil->removeFromParent();
    clip->setStencil( m_clip_stencil );
    clip->setAlphaThreshold(0.1f);
    root->addChild(clip);

    CacheGif* gif = CacheGif::create( playshared.getJigsaw().c_str() );
    gif->setScale( m_clip_stencil->getContentSize().width/gif->getContentSize().width );
    gif->setPosition(m_clip_stencil->getPosition());
    clip->addChild(gif);

	return true;
}

Node* PlayDisplay::load_csd()
{
	Node* root = CSLoader::createNode("Preview.csb");

//	Button* btn = nullptr;


	m_back = static_cast<ImageView*>( root->getChildByName("back") );
    m_clip_stencil = static_cast<ImageView*>( root->getChildByName("clip_stencil") );
//    m_img_back = static_cast<ImageView*>( root->getChildByName("Image_3") );

	return root;
}

void PlayDisplay::onTouchPanel(Ref*, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        getCurScene()->dismiss(this);
    }
}



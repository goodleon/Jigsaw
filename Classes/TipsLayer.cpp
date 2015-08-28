

#include "TipsLayer.h"

TipsLayer::TipsLayer()
{

}

TipsLayer::~TipsLayer()
{

}

bool TipsLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    auto callback = std::bind(&TipsLayer::onTouchPanel, this, placeholders::_1, placeholders::_2);
    m_panel->addTouchEventListener( callback );

	return true;
}

Node* TipsLayer::load_csd()
{
	Node* root = CSLoader::createNode("tips.csb");

//	Button* btn = nullptr;


	m_panel = static_cast<Layout*>(root->getChildByName("panel"));


	return root;
}

void TipsLayer::onTouchPanel(Ref*,Widget::TouchEventType evt)
{
    Return_If(evt != Widget::TouchEventType::ENDED);
    getCurScene()->removeChild(this);
}

void TipsLayer::addContent(cocos2d::Node* content)
{
    addChild(content);
    Point pt = content->getPosition();
    Rect rc = content->getBoundingBox();
    Size win = cocos2d::Director::getInstance()->getWinSize();
    if (rc.origin.x < 0)
    {
        pt.x += rc.origin.x;
    }
}

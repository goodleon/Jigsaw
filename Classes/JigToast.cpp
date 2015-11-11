

#include "JigToast.h"
#include "LanguageMgr.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;

void JigToast::show(const std::string& lan_id)
{
    const Size win = Director::getInstance()->getWinSize();
    JigToast* toast = JigToast::create();
    toast->m_text->setString( LanguageMgr::inst().getText(lan_id) );
    toast->setPosition( win/2 );
    
    auto remove = [=](){
        toast->removeFromParent();
    };
    Sequence* seq = Sequence::create( MoveBy::create(2.0f, Point(0,win.height/4)), CallFunc::create(remove), NULL);
    toast->runAction(seq);
    
    seq = Sequence::create( DelayTime::create(0.5f), FadeOut::create(1.5f), NULL);
    toast->m_text->runAction( seq );
    
    Director::getInstance()->getRunningScene()->addChild( toast );
}

JigToast::JigToast()
{

}

JigToast::~JigToast()
{

}

bool JigToast::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

Node* JigToast::load_csd()
{
	Node* root = CSLoader::createNode("Toast.csb");

//	Button* btn = nullptr;


	m_text = static_cast<Text*>(root->getChildByName("text"));


	return root;
}





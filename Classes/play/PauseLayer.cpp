

#include "PauseLayer.h"
#include "ChooseLayer.h"

PauseLayer::PauseLayer()
{

}

PauseLayer::~PauseLayer()
{

}

bool PauseLayer::init()
{
	Return_False_If(!Layer::init());

	load_csd();

	return true;
}

void PauseLayer::load_csd()
{
	Node* root = CSLoader::createNode("pause.csb");
	addChild(root);

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Continue") );
	btn->addClickEventListener( std::bind(&PauseLayer::onClickContinue, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Mainmenu") );
	btn->addClickEventListener( std::bind(&PauseLayer::onClickMainmenu, this, placeholders::_1) );


}


void PauseLayer::onClickContinue(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);
//	CCLOG("%s", btn->getName().c_str());
    playshared.play_scene->popLayer();
}
			
void PauseLayer::onClickMainmenu(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);
//	CCLOG("%s", btn->getName().c_str());
    Scene* scene = ChooseLayer::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}




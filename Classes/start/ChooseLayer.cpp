//
//  ChooseScene.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-17.
//
//

#include "ChooseLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PlayLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;

ChooseLayer::ChooseLayer()
{
    
}

ChooseLayer::~ChooseLayer()
{
    
}

Scene* ChooseLayer::createScene()
{
    Scene* scene = Scene::create();
    ChooseLayer* layer = ChooseLayer::create();
    scene->addChild(layer);
    return scene;
}

bool ChooseLayer::init()
{
    Layer::init();
    
    Node* root = CSLoader::createNode("choose.csb");
    addChild(root);
    
    Button* start = root->getChildByName<Button*>("start");
    start->addClickEventListener( std::bind(&ChooseLayer::onStartClick, this, std::placeholders::_1) );
    
    return true;
}

void ChooseLayer::onStartClick(cocos2d::Ref* button)
{
    Scene* play = PlayLayer::createScene();
    Director::getInstance()->replaceScene(play);
}



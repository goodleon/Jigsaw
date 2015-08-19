

#include "PlayLayer.h"
#include "TouchPanel.h"
#include "JigBackground.h"
#include "JigScene.h"
#include "PlayMainboard.h"


using namespace cocos2d::ui;

PlayLayer::PlayLayer()
{
	
}

PlayLayer::~PlayLayer()
{
    
}

Scene* PlayLayer::createScene()
{
    JigScene* scene = JigScene::create();
    PlayLayer* layer = PlayLayer::create();
    scene->pushLayer(layer);
    
    playshared.play_scene = scene;
    return scene;
}

bool PlayLayer::init()
{
    Return_False_If(!Layer::init());
    
    Sprite* sp = Sprite::create("back.png");
    addChild(sp);
    centerInParent(sp);
    
    JigBackground* back = JigBackground::create();
    addChild(back);
    
    SpriteFrame* sf = addSpriteFrameByFile("HelloWorld.png");
    
    TouchPanel* panel = TouchPanel::create();
    panel->reset(sf, 2, 2);
    addChild(panel);
    centerInParent(panel);
    
    PlayMainboard* board = PlayMainboard::create();
    addChild(board);
    
    return true;
}



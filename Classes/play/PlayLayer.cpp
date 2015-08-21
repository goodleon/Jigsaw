

#include "PlayLayer.h"
#include "RotableTouchPanel.h"
#include "JigBackground.h"
#include "JigScene.h"
#include "PlayMainboard.h"


using namespace cocos2d::ui;

PlayLayer::PlayLayer()
{
	
}

PlayLayer::~PlayLayer()
{
    playshared.play_scene = nullptr;
    playshared.jig_panel = nullptr;
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
    
    playshared.jig_panel = RotableTouchPanel::create();
    playshared.jig_panel->reset(sf, 4, 4);
    addChild(playshared.jig_panel);
    playshared.jig_panel->setPosition(getContentSize()/2);
    
    PlayMainboard* board = PlayMainboard::create();
    addChild(board);
    
    return true;
}



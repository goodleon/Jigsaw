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

//    std::map<std::string,float> dd;
//    {
//        FILE* fp = fopen("/Users/zhangdw/work/note/cfg.txt", "r");
//        while (!feof(fp)) {
//            char key[256] = {0};
//            float value = 0;
//            fscanf(fp, "%[^=]=%f\n", key, &value);
//            if(!strcmp(key, "error")){
//                assert(false);
//            }
//            else if (strcmp(key, "")) {
//                dd[key] = value;
//            }
//        }
//        fclose(fp);
//        for(auto it = dd.begin(); it != dd.end(); ++it)
//        {
//            printf("zz:%s=%f\n", it->first.c_str(), it->second);
//        }
//    }
//    
//    removeChildByTag(100);
//    
//    SpriteFrame* sf = addSpriteFrameByFile("HelloWorld.png");
//    JigTile* tile = JigTile::create();
//    tile->setTag(100);
//    tile->setRawFrame(sf);
//    tile->setRawRect(Rect(120, 120, 240, 240));
//    
//    vector<EdgeType> edges;
//    edges.push_back( (EdgeType)(int)dd["up"] );
//    edges.push_back( (EdgeType)(int)dd["right"] );
//    edges.push_back( (EdgeType)(int)dd["down"] );
//    edges.push_back( (EdgeType)(int)dd["left"] );
//    tile->setEdges(edges);
//    
//    addChild(tile);
//    tile->setPosition( getContentSize()/2 );
}



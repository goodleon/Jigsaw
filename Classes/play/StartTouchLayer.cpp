//
//  StartTouchLayer.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-25.
//
//

#include "StartTouchLayer.h"
#include "GameState.h"

StartTouchLayer::StartTouchLayer()
{
    
}

StartTouchLayer::~StartTouchLayer()
{
    
}

bool StartTouchLayer::init()
{
    Return_False_If(!Layer::init());
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = std::bind(&StartTouchLayer::onTouchBegan, this, placeholders::_1, placeholders::_2);
    listener->onTouchMoved = std::bind(&StartTouchLayer::onTouchMoved, this, placeholders::_1, placeholders::_2);
    listener->onTouchEnded = std::bind(&StartTouchLayer::onTouchEnded, this, placeholders::_1, placeholders::_2);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool StartTouchLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void StartTouchLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}

void StartTouchLayer::onTouchEnded(Touch* touch, Event* event)
{
//    if () {
//        <#statements#>
//    }
}


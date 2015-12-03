//
//  JigLayer.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-3.
//
//

#include "JigLayer.h"

JigLayer::JigLayer()
{

}

JigLayer::~JigLayer()
{

}

void JigLayer::onExit()
{
    Layer::onExit();
    if (onExitEvent) {
        onExitEvent(this);
    }
}
//
//  JigBackground.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-18.
//
//

#include "JigBackground.h"

JigBackground::JigBackground()
{
    
}

JigBackground::~JigBackground()
{
    
}

bool JigBackground::init()
{
    Return_False_If(!Layer::init());
    
    Sprite* sp = Sprite::create("HelloWorld.png");
    sp->setOpacity(100);
    addChild(sp);
    centerInParent(sp);
    
    return true;
}



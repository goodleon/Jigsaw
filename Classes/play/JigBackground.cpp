//
//  JigBackground.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-18.
//
//

#include "JigBackground.h"

JigBackground::JigBackground()
:m_jigsaw(nullptr)
{
    
}

JigBackground::~JigBackground()
{
    
}

bool JigBackground::init()
{
    Return_False_If(!Layer::init());
    
    return true;
}

void JigBackground::reset(SpriteFrame* jigsaw, int rows, int cols)
{
    setContentSize( jigsaw->getRect().size );
    
    Sprite* back = Sprite::createWithSpriteFrame(jigsaw);
    back->setPosition( getContentSize()/2 );
    back->setOpacity(50);
    addChild(back);
    
    DrawNode* draw = DrawNode::create();
    addChild(draw);
    
    const Size tileSize( getContentSize().width/cols, getContentSize().height/rows );
    
    for (int r=0; r<=rows; ++r)
    {
        Point src( 0, tileSize.height*r );
        Point dst( getContentSize().width, tileSize.height*r );
        draw->drawLine(src, dst, Color4F{0.5f, 0.5f, 0.5f, 1.0f});
    }
    
    for (int c=0; c<=cols; ++c)
    {
        Point src( tileSize.width*c, 0 );
        Point dst( tileSize.width*c, getContentSize().height );
        draw->drawLine(src, dst, Color4F{0.5f, 0.5f, 0.5f, 1.0f});
    }
}



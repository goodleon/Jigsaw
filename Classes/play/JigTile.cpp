//
//  JigTile.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-17.
//
//

#include "JigTile.h"
#include "TempShadow.h"

JigTile::JigTile()
:m_edge(nullptr)
{
    m_edge = DrawNode::create();
    m_edge->setLocalZOrder(100);
    addChild(m_edge);
}

JigTile::~JigTile()
{
    
}

bool JigTile::init()
{
    Return_False_If(!ClippingNode::init());
    
    setAnchorPoint(Point::ANCHOR_MIDDLE);
    
    setAlphaThreshold(0.5f);
    
    return true;
}

void JigTile::setRawFrame(SpriteFrame* frame)
{
    removeAllChildren();
    
    m_display = Sprite::createWithSpriteFrame(frame);
    m_display->setAnchorPoint(Point::ZERO);
    addChild(m_display);
    
    m_display->setVisible(false);
}

void JigTile::setRawRect(const Rect& rc)
{
    setContentSize(rc.size);
  
    m_edge->clear();
    m_edge->drawRect(Point::ZERO, rc.size/2, Color4F(1.0f, 0.5f, 0.5f, 1.0f));
    
    vector<EdgeType> edges;
    edges.push_back(ET_A);
    edges.push_back(ET_V);
    edges.push_back(ET_A);
    edges.push_back(ET_V);
    
    TempShadow* shadow = TempShadow::create();
    shadow->setSquareSize(rc.size);
    shadow->setAnchorPoint(Point::ZERO);
    shadow->setEdgeType(edges);
    setStencil(shadow);
    
    Size size = m_display->getContentSize();
    Point pt_in_tex;
    pt_in_tex.x = -rc.origin.x;
    pt_in_tex.y = rc.origin.y+rc.size.height-size.height;
    
    m_display->setPosition(pt_in_tex);
}



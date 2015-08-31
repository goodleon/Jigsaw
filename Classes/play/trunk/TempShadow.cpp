//
//  TempShadow.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-18.
//
//

#include "TempShadow.h"
#include "cex.h"
#include "PlayShared.h"

TempShadow::TempShadow()
{

}

TempShadow::~TempShadow()
{
    
}

bool TempShadow::init()
{
    Return_False_If(!Sprite::init());
    
    return true;
}

void TempShadow::setSquareSize(const Size& size)
{
    float scaleX = size.width/100;
    float scaleY = size.height/100;
    m_scale = min(scaleX, scaleY);
    
    setContentSize(size);
}

Size TempShadow::getSquareSize()
{
    return Size(m_scale*100, m_scale*100);
}

float TempShadow::getSquareScale()
{
    return m_scale;
}

void TempShadow::setEdgeType(const std::vector<EdgeType>& edges)
{
    removeAllChildren();
    
    m_shadow = ShadowCommand::createShadowByEdges(edges);
    m_shadow->setScale(m_scale);
    m_shadow->setPosition(getContentSize()/2);
    addChild(m_shadow);
    
    m_edges = edges;
}

std::vector<EdgeType> TempShadow::getEdgeType()
{
    return m_edges;
}



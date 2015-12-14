//
//  JigTile.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-17.
//
//

#include "JigTile.h"

JigTile::JigTile()
:m_index(-1)
{
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

void JigTile::setRawDisplay(const string& file)
{
    removeAllChildren();

    m_display = JigSprite::create(file.c_str());
    m_display->setAnchorPoint(Point::ZERO);
    addChild(m_display);
}

void JigTile::setRawRect(const Rect& rc)
{
    setContentSize(rc.size);
    
    Size size = m_display->getContentSize();
    Point pt_in_tex;
    pt_in_tex.x = -rc.origin.x;
    pt_in_tex.y = rc.origin.y+rc.size.height-size.height;
    
    m_display->setPosition(pt_in_tex);
}

void JigTile::setEdges(const std::vector<EdgeType>& edges)
{
    TempShadow* shadow = TempShadow::create();
    shadow->setSquareSize( getContentSize() );
    shadow->setPosition( getContentSize()/2 );
    shadow->setEdgeType(edges);
    setStencil(shadow);
    this->setAlphaThreshold(0.1f);

    Sprite* red = ShadowCommand::createShadowByEdges(edges);
    red->setPosition( getContentSize()/2 );
    BlendFunc bf;
    bf.src = GL_ONE;
    bf.dst = GL_SRC_ALPHA;
    red->setScale( shadow->getSquareScale() );
    red->setBlendFunc(bf);
    this->addChild(red);
}

std::vector<EdgeType> JigTile::getEdges()
{
    TempShadow* shadow = static_cast<TempShadow*>( getStencil() );
    return shadow->getEdgeType();
}

void JigTile::setDirection(Direction dir)
{
    float angle = dir.toint() * 90;
    runAction( RotateTo::create(0.1f, angle) );
}

Direction JigTile::getDirection()
{
    int dir = getRotation() / 90;
    return Direction( (DirectionType)(dir%4) );
}

void JigTile::setIndex(int index)
{
    m_index = index;
    CCASSERT(m_index>=0, "");
}

int JigTile::getIndex() const
{
    CCASSERT(m_index>=0, "");
    return m_index;
}

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
:m_square(nullptr)
{

}

TempShadow::~TempShadow()
{
    
}

TempShadow* TempShadow::create()
{
    TempShadow* ret = new TempShadow();
    ret->init();
    return ret;
}

bool TempShadow::init()
{
    Return_False_If(!ClippingNode::init());
    
    m_square = Sprite::create("sd_square.png");
    m_square->setAnchorPoint(Point::ZERO);
    addChild(m_square);
    
    this->setInverted( true );
    this->setAlphaThreshold(0.5f);
    
    return true;
}

void TempShadow::setSquareSize(const Size& size)
{
    setContentSize(size);
    
    Size cur = getSquareSize();
    m_square->setScale(size.width/cur.width, size.height/cur.height);
}

Size TempShadow::getSquareSize()
{
    return m_square->getBoundingBox().size;
}

Size TempShadow::getFullSize()
{
    CCASSERT(false, "");
    return getSquareSize();
}

void TempShadow::setEdgeType(std::vector<EdgeType>& edges)
{
    this->setStencil( createSubCircles(edges) );
    
    for (int i=0; i<edges.size(); ++i)
    {
        if (edges.at(i) == ET_A)
        {
            Sprite* sp = Sprite::create("sd_circle.png");
            addChild(sp);
            configCircle(sp, i);
        }
    }
}

void TempShadow::configCircle(Sprite* circle, int index)
{
    const Size con = getContentSize();
    Point pts[] = {
        Point(0, con.height)
        ,Point(con.width, con.height)
        ,Point(con.width, 0)
        ,Point(0, 0)
    };
    
    Point start = pts[index];
    Point end = pts[(index+1)%4];
    Point center = start.getMidpoint(end);
    circle->setPosition(center);
}

Node* TempShadow::createSubCircles(std::vector<EdgeType>& edges)
{
    Node* sub_circle = Node::create();
    for (int i=0; i<edges.size(); ++i)
    {
        if (edges.at(i) == ET_V)
        {
            Sprite* circle = Sprite::create("sd_circle.png");
            sub_circle->addChild(circle);
            configCircle(circle, i);
        }
    }
    return sub_circle;
}


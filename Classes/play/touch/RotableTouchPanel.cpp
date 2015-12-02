

#include "RotableTouchPanel.h"

RotableTouchPanel::RotableTouchPanel()
{
	
}

RotableTouchPanel::~RotableTouchPanel()
{
    
}

void RotableTouchPanel::startTile(int index, const Point &pt)
{
    DelayTime* delay = DelayTime::create(0.1f*index+0.5f);
    MoveTo* move = MoveTo::create(0.2f, pt);
    m_tiles.at(index)->runAction( Sequence::create(delay, move, NULL) );

    DirectionType dir = (DirectionType)(rand()%4);
    m_tiles.at(index)->setDirection( Direction( dir ) );
}

void RotableTouchPanel::onClickTile(Touch* touch)
{
    Return_If(!m_touching);
    
    Direction dir = m_touching->getDirection();
    m_touching->setDirection( dir.next() );

    notifyEvent(TPE_Click);
}


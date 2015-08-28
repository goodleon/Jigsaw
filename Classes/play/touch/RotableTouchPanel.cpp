

#include "RotableTouchPanel.h"

RotableTouchPanel::RotableTouchPanel()
{
	
}

RotableTouchPanel::~RotableTouchPanel()
{
    
}

void RotableTouchPanel::onClickTile(Touch* touch)
{
    Return_If(!m_touching);
    
    Direction dir = m_touching->getDirection();
    m_touching->setDirection( dir.next() );
}

void RotableTouchPanel::setStartRect(const Rect& rc)
{
    DragonlyTouchPanel::setStartRect(rc);
    
    for (int i=0; i<m_tiles.size(); ++i)
    {
        DirectionType dir = (DirectionType)(rand()%4);
        m_tiles.at(i)->setDirection( Direction( dir ) );
    }
}

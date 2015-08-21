

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



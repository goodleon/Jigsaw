

#include "DragonlyTouchPanel.h"

DragonlyTouchPanel::DragonlyTouchPanel()
{
	
}

DragonlyTouchPanel::~DragonlyTouchPanel()
{
    
}

void DragonlyTouchPanel::startTile(int index, const Point& pt)
{
//    DelayTime* delay = DelayTime::create(0.1f*index+0.5f);
//    MoveTo* move = MoveTo::create(0.2f, pt);
//    m_tiles.at(index)->runAction( Sequence::create(delay, move, NULL) );
}

void DragonlyTouchPanel::onClickTile(Touch* touch)
{
    
}
void DragonlyTouchPanel::onDragBegan(Touch* touch)
{
    Return_If(!m_touching);
    
    const Point pt = this->convertToNodeSpace( touch->getLocation() );
    m_touchOffset = pt - m_touching->getPosition();
    
    selectTile(m_touching);
}

void DragonlyTouchPanel::onDragMoved(Touch* touch)
{
    Return_If(!m_touching);
    
    const Point pt = this->convertToNodeSpace( touch->getLocation() );
    m_touching->setPosition( pt-m_touchOffset );
}

void DragonlyTouchPanel::onDragEnded(Touch* touch)
{
    Return_If(!m_touching);
    
    const Point local_pt = m_touching->getPosition();
    const Rect local_rc(0, 0, getContentSize().width, getContentSize().height);
    if (local_rc.containsPoint(local_pt))
    {
        int r = local_pt.y / m_tileSize.height;
        int c = local_pt.x / m_tileSize.width;
        
        Point center( (c+0.5f)*m_tileSize.width, (r+0.5f)*m_tileSize.height );
        Rect rc( center.x-50, center.y-50, 100, 100 );
        
        if (rc.containsPoint(local_pt))
            m_touching->setPosition( center );
    }
    else
    {
        const Size win = Director::getInstance()->getWinSize();
        const Point world_pt = this->convertToWorldSpace( local_pt );
        
        Point pt = world_pt;
        
        pt.x = MAX(pt.x, 0);
        pt.x = MIN(pt.x, win.width);
        pt.y = MAX(pt.y, 0);
        pt.y = MIN(pt.y, win.height);
        
        pt = this->convertToNodeSpace(pt);
        m_touching->setPosition( pt );
    }
}

void DragonlyTouchPanel::selectTile(JigTile* tile)
{
    tile->setLocalZOrder(1);
    
    auto pre_touched = std::find_if(m_tiles.begin(), m_tiles.end(), [=](JigTile* tile){
        return tile->getLocalZOrder()==1;
    });
    if (pre_touched != m_tiles.end())
        (*pre_touched)->setLocalZOrder(0);
}
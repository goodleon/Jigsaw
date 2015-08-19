

#include "TouchPanel.h"

TouchPanel::TouchPanel()
:m_touching(nullptr)
{
	
}

TouchPanel::~TouchPanel()
{
    
}

bool TouchPanel::init()
{
    Return_False_If(!Sprite::init());
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = std::bind(&TouchPanel::onTouchBegan, this, placeholders::_1, placeholders::_2);
    listener->onTouchMoved = std::bind(&TouchPanel::onTouchMoved, this, placeholders::_1, placeholders::_2);
    listener->onTouchEnded = std::bind(&TouchPanel::onTouchEnded, this, placeholders::_1, placeholders::_2);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void TouchPanel::reset(cocos2d::SpriteFrame* sf, int rows, int cols)
{
    clear();
    
    const Size raw_size( sf->getOriginalSize() );
    const Size tile_size( raw_size.width/cols, raw_size.height/rows );
    
    m_tileSize = tile_size;
    m_splitRows = rows;
    m_splitCols = cols;
    
    this->setContentSize( raw_size );
    
    //reset tiles
    for (int i=0; i<rows; ++i)
    {
        for (int j=0; j<cols; ++j)
        {
            JigTile* tile = JigTile::create();
//            if (!(i==0 && j==0))
//                continue;
            {
                addChild(tile);
                m_tiles.push_back(tile);
            }
            
            tile->setRawFrame(sf);
            
            Rect rc(j*tile_size.width, i*tile_size.height, tile_size.width, tile_size.height);
            tile->setRawRect(rc);
            
            CCASSERT(tile->getAnchorPoint()==Point::ANCHOR_MIDDLE, "");
            Point pt = cocos2array( rc.origin, this );
            pt.x += tile_size.width/2;
            pt.y -= tile_size.height/2;
            tile->setPosition( pt );
        }
    }
}

bool TouchPanel::onTouchBegan(Touch* touch, Event* event)
{
    const Point pt = this->convertToNodeSpace( touch->getLocation() );
    
    auto touched_tile = std::find_if(m_tiles.begin(), m_tiles.end(), [=](JigTile* tile){
        Rect rc;
        rc.origin = tile->getPosition() - tile->getContentSize()/2;
        rc.size = tile->getContentSize();
        return rc.containsPoint(pt);
    });
    m_touching = touched_tile==m_tiles.end() ? nullptr : *touched_tile;
    if (m_touching)
    {
        m_touching->setLocalZOrder(1);
        m_touchOffset = pt - m_touching->getPosition();
    }
    
    auto pre_touched = std::find_if(m_tiles.begin(), m_tiles.end(), [=](JigTile* tile){
        return tile->getLocalZOrder()==1;
    });
    if (pre_touched != m_tiles.end())
        (*pre_touched)->setLocalZOrder(0);
    
    return (m_touching!=nullptr);
}

void TouchPanel::onTouchMoved(Touch* touch, Event* event)
{
    Return_If(!m_touching);
    
    const Point pt = this->convertToNodeSpace( touch->getLocation() );
    m_touching->setPosition( pt-m_touchOffset );
}

void TouchPanel::onTouchEnded(Touch* touch, Event* event)
{
    const Point local_pt = m_touching->getPosition();
    const Point world_pt = this->convertToWorldSpace( local_pt );
    
    if (this->getBoundingBox().containsPoint(world_pt))
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
        
        Point pt = world_pt;
        
        pt.x = MAX(pt.x, 0);
        pt.x = MIN(pt.x, win.width);
        pt.y = MAX(pt.y, 0);
        pt.y = MIN(pt.y, win.height);
        
        pt = this->convertToNodeSpace(pt);
        m_touching->setPosition( pt );
    }

    m_touching = nullptr;
}

void TouchPanel::clear()
{
    removeAllChildren();
    m_touching = nullptr;
    m_tiles.clear();
}

//Point TouchPanel::cocos2array(int x, int y)
//{
//    cocos2d::Size size = getContentSize();
//    return cocos2d::Point(x, size.height-y);
//}

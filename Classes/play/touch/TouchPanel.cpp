

#include "TouchPanel.h"

TouchPanel::TouchPanel()
:m_touching(nullptr)
,m_touch_type(Touch_None)
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
    
    m_tileSize.setSize( raw_size.width/cols, raw_size.height/rows );
    m_splitRows = rows;
    m_splitCols = cols;
    
    setContentSize( raw_size );
    
    initTiles(sf);
    initEdges();
}

bool TouchPanel::isAllFinished()
{
    auto is_placed_well = [=](int r, int c){
        Rect correct;
        correct.origin = Point(c*m_tileSize.width, r*m_tileSize.height) + m_tileSize/2 - Point(3,3);
        correct.size.setSize(6, 6);
        JigTile* tile = m_tiles.at( r*m_splitCols + c );
        Point tile_at = cocos2array(tile->getPosition(), this);
        if (correct.containsPoint(tile_at) && tile->getDirection()==DT_UP)
        {
            return true;
        }
        return false;
    };
    
    for (int r=0; r<m_splitRows; ++r)
    {
        for (int c=0; c<m_splitCols; ++c)
        {
            if (!is_placed_well(r, c))
                return false;
        }
    }
    return true;
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
    onDragBegan( touch );
    
    this->scheduleOnce( SEL_SCHEDULE(&TouchPanel::longTouchCallback), 0.5f );
    
    return true;
}

void TouchPanel::onTouchMoved(Touch* touch, Event* event)
{
    if (m_touch_type == Touch_None)
    {
        int dis = touch->getLocation().distance( touch->getStartLocation() );
        if (dis > 10)
        {
            m_touch_type = Touch_Drag;
        }
    }
    
    if (m_touch_type == Touch_Drag)
    {
        onDragMoved(touch);
    }
}

void TouchPanel::onTouchEnded(Touch* touch, Event* event)
{
    if (m_touch_type == Touch_Drag)
    {
        onDragEnded(touch);
    }
    else if (m_touch_type == Touch_None)
    {
        onClickTile(touch);
    }

    m_touch_type = Touch_None;
    this->unschedule(SEL_SCHEDULE(&TouchPanel::longTouchCallback));
    m_touching = nullptr;
}

void TouchPanel::clear()
{
    removeAllChildren();
    m_touching = nullptr;
    m_tiles.clear();
}

void TouchPanel::initTiles(SpriteFrame* sf)
{
    for (int i=0; i<m_splitRows; ++i)
    {
        for (int j=0; j<m_splitCols; ++j)
        {
            JigTile* tile = JigTile::create();
            addChild(tile);
            m_tiles.push_back(tile);
            
            tile->setRawFrame(sf);
            
            Rect rc(j*m_tileSize.width, i*m_tileSize.height, m_tileSize.width, m_tileSize.height);
            tile->setRawRect(rc);
            
            CCASSERT(tile->getAnchorPoint()==Point::ANCHOR_MIDDLE, "");
            Point pt = cocos2array( rc.origin, this );
            pt.x += m_tileSize.width/2;
            pt.y -= m_tileSize.height/2;
            tile->setPosition( pt );
        }
    }
}

void TouchPanel::initEdges()
{
    auto up_type = [=](int r, int c){
        if (r==0) {
            return ET_F;
        }
        else{
            int index = (r-1)*m_splitRows + c;
            return m_tiles.at(index)->getEdges().at(DT_DOWN);
        }
    };
    
    auto left_type = [=](int r, int c){
        if (c==0) {
            return ET_F;
        }
        else{
            int index = r*m_splitCols + c-1;
            return m_tiles.at(index)->getEdges().at(DT_RIGHT);
        }
    };
    
    auto revert_type = [](EdgeType type){
        if (type == ET_A) {
            return ET_V;
        }
        else if (type == ET_F){
            return ET_F;
        }
        else if (type == ET_V){
            return ET_A;
        }
        assert(false);
        return ET_F;
    };
    
    auto rand_type_right = [=](int c){
        if (c==m_splitCols-1) {
            return ET_F;
        }
        else{
            return rand()%2 ? ET_A : ET_V;
        }
    };
    
    auto rand_type_down = [=](int r){
        if (r==m_splitRows-1) {
            return ET_F;
        }
        else{
            return rand()%2 ? ET_A : ET_V;
        }
    };
    
    for (int r=0; r<m_splitRows; ++r)
    {
        for (int c=0; c<m_splitCols; ++c)
        {
            std::vector<EdgeType> edges(4);
            edges.at(DT_UP) = revert_type( up_type(r, c) );
            edges.at(DT_LEFT) = revert_type( left_type(r, c) );
            edges.at(DT_RIGHT) = rand_type_right(c);
            edges.at(DT_DOWN) = rand_type_down(r);
            
            m_tiles.at( r*m_splitCols + c )->setEdges( edges );
            
            printf("r=%d,c=%d,edge=%d%d%d%d\n", r, c, edges.at(0), edges.at(1), edges.at(2), edges.at(3));
        }
    }
}

void TouchPanel::longTouchCallback(float delay)
{
    m_touch_type = Touch_Drag;
}

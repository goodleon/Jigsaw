

#include "TouchPanel.h"
#include "GameState.h"

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

    setColor(Color3B{255,255,0});
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = std::bind(&TouchPanel::onTouchBegan, this, placeholders::_1, placeholders::_2);
    listener->onTouchMoved = std::bind(&TouchPanel::onTouchMoved, this, placeholders::_1, placeholders::_2);
    listener->onTouchEnded = std::bind(&TouchPanel::onTouchEnded, this, placeholders::_1, placeholders::_2);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void TouchPanel::reset(const string& file, int rows, int cols)
{
    CCLOG("ddd:reset0");
    clear();

    CCLOG("ddd:reset1");

    CacheGif* gif = CacheGif::create(file.c_str());
    CCLOG("ddd:reset2:%p:%s", gif, file.c_str());
    const Size raw_size = gif->getContentSize();
    CCLOG("ddd:reset3");

    m_tileSize.setSize( raw_size.width/cols, raw_size.height/rows );
    m_splitRows = rows;
    m_splitCols = cols;
    
    setContentSize( raw_size );

    CCLOG("ddd:reset4");
    initTiles(file);
    CCLOG("ddd:reset5");
    initEdges();
    CCLOG("ddd:reset6");
    initBackLines();
    CCLOG("ddd:reset7");
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
    Return_False_If(!canTouch());
    
    const Point pt = this->convertToNodeSpace( touch->getLocation() );
    auto touched_tile = std::find_if(m_tiles.rbegin(), m_tiles.rend(), [=](JigTile* tile){
        Rect rc;
        rc.origin = tile->getPosition() - tile->getContentSize()/2;
        rc.size = tile->getContentSize();
        return rc.containsPoint(pt);
    });
    
    m_touching = touched_tile==m_tiles.rend() ? nullptr : *touched_tile;
    onDragBegan( touch );
    
    this->scheduleOnce( SEL_SCHEDULE(&TouchPanel::longTouchCallback), 0.5f );
    
    startGame();
    
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

    checkGameState();

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

void TouchPanel::initTiles(const string& gif_file)
{
    for (int i=0; i<m_splitRows; ++i)
    {
        for (int j=0; j<m_splitCols; ++j)
        {
            JigTile* tile = JigTile::create();
            addChild(tile);
            m_tiles.push_back(tile);

            tile->setRawDisplay(gif_file);

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
        }
    }
}

void TouchPanel::initBackLines()
{
    const Color4F color(1.0f,0,0,1.0f);
    DrawNode* node = DrawNode::create();

    for (int i=0; i<=m_splitRows; ++i) {
        node->drawSegment(Point(0,i*m_tileSize.height), Point(getContentSize().width, i*m_tileSize.height), 1.0f, color);
    }

    for (int i=0; i<=m_splitCols; ++i) {
        node->drawSegment(Point(i*m_tileSize.width, 0), Point(i*m_tileSize.width, getContentSize().height), 1.0f, color);
    }

//    node->drawRect(Point(0,0), getContentSize(), color);

    addChild(node);
}

void TouchPanel::longTouchCallback(float delay)
{
    m_touch_type = Touch_Drag;
}

void TouchPanel::setStartRect(const Rect& rc)
{
    Rect real = rc;
    real.origin += m_tileSize/2;
    real.size.setSize( real.size.width-m_tileSize.width, real.size.height-m_tileSize.height );
    
    for (int i=0; i<m_tiles.size(); ++i)
    {
        int x = rand_0_1() * real.size.width + real.origin.x;
        int y = rand_0_1() * real.size.height + real.origin.y;

        DelayTime* delay = DelayTime::create(0.2f*i+0.5f);
        MoveTo* move = MoveTo::create(0.3f, Point(x, y));
        m_tiles.at(i)->runAction( Sequence::create(delay, move, NULL) );
    }
}

void TouchPanel::startGame()
{
    if (GameStateMgr::inst().curState()==gs_prepare && m_touching)
    {
        GameStateMgr::inst().change(gs_playing);
    }
}

void TouchPanel::checkGameState()
{
    if (GameStateMgr::inst().curState()==gs_prepare) {
        return;
    }

    if(GameStateMgr::inst().curState()!=gs_win && isAllFinished())
    {
        GameStateMgr::inst().change(gs_win);
    }
    else if (GameStateMgr::inst().curState()==gs_win && !isAllFinished())
    {
        GameStateMgr::inst().change(gs_playing);
    }
}

bool TouchPanel::canTouch()
{
    return GameStateMgr::inst().curState()==gs_prepare
        || GameStateMgr::inst().curState()==gs_playing
        || GameStateMgr::inst().curState()==gs_win;
}